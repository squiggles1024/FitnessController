/*
 * FitnessController.c
 *
 *  Created on: Jul 11, 2022
 *      Author: evanl
 */


#include <stdint.h>
#include <stdio.h>
#include "bluenrg_utils.h"
#include "bluenrg_conf.h"
#include "hci.h"
#include "bluenrg_types.h"
#include "bluenrg_gap.h"
#include "bluenrg_aci.h"
#include "hci_le.h"
#include "FitnessController.h"
#include "HIDService.h"
#include "BatteryService.h"
#include "DeviceInfoService.h"
#include "HID.h"

#define DEVICE_CONNECTABLE (1)
#define DEVICE_CONNECTED (0)
#define XINPUT_LEFT_THUMB_INDEX  (6U)
#define XINPUT_RIGHT_THUMB_INDEX (7U)
#define XINPUT_LEFTANALOG_INDEX (0U)
#define XINPUT_RIGHTANALOG_INDEX (1U)

FitnessControllerHandle_t FitnessController;

static const uint8_t SERVER_BDADDR[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
static const char local_name[] = {AD_TYPE_COMPLETE_LOCAL_NAME,'F', 'i', 't', 'n', 'e','s','s',' ','C','o','n','t','r','o','l','l','e','r'};
static uint8_t connected = DEVICE_CONNECTABLE;
static void AddServices(void);
static tBleStatus SetConnectable(void);
static void ControllerEventNotify(void *pData);
static void ControllerButtonInit(FitnessControllerHandle_t *FitnessController);
static void ControllerTriggerInit(FitnessControllerHandle_t *FitnessController);
static void ControllerStickInit(FitnessControllerHandle_t *FitnessController);
static const uint16_t ButtonMskLUT[NUMBER_OF_BUTTONS] = {
		0x0001, //dpad up
		0x0002, //dpad down
		0x0004, //dpad left
		0x0008, //dpad right
		0x0010, //start
		0x0020, //back
		0x0040, //left thumb
		0x0080, //right thumb
		0x0100, //left shoulder
		0x0200, //right shoulder
		0x1000, //a
		0x2000, //b
		0x4000, //x
		0x8000  //y
};


void FitnessControllerBLEInit(void){
	tBleStatus status; //Var for storing return status

	uint8_t bdaddr[BD_ADDR_SIZE]; //Device address
	const char *DeviceName = "Evan's Fitness Controller"; //Device Name
	uint16_t service_handle,  dev_name_char_handle, appearance_char_handle;
	uint8_t hwVersion;
	uint16_t fwVersion;

	BLUENRG_memcpy(bdaddr, SERVER_BDADDR, sizeof(SERVER_BDADDR));
	//Init HCI
	hci_init(ControllerEventNotify,NULL);
	getBlueNRGVersion(&hwVersion, &fwVersion);
	hci_reset();
	HAL_Delay(100);

	status = aci_hal_write_config_data(CONFIG_DATA_PUBADDR_OFFSET, CONFIG_DATA_PUBADDR_LEN, bdaddr);

	if(status != BLE_STATUS_SUCCESS){
		printf("aci_hal_write_config_data failed\n\r");
		while(1);
	}

	status = aci_gatt_init();
	if(status != BLE_STATUS_SUCCESS){
		printf("aci_gatt_init failed\n\r");
		while(1);
	}


    status = aci_gap_init_IDB05A1(GAP_PERIPHERAL_ROLE_IDB05A1, 0, strlen(DeviceName), &service_handle, &dev_name_char_handle, &appearance_char_handle);
	if(status != BLE_STATUS_SUCCESS){
		printf("aci_gap_init failed\n\r");
		while(1);
	}


	status = aci_gatt_update_char_value(service_handle, dev_name_char_handle, 0, strlen(DeviceName), DeviceName);
	if(status != BLE_STATUS_SUCCESS){
		printf("aci_gatt_update_char_value failed\n\r");
		while(1);
	}
	uint16_t test_appearance_value = 0x03C4;
	status = aci_gatt_update_char_value(service_handle,appearance_char_handle,0,2,&test_appearance_value);
	AddServices();


}

void FitnessController_BLE_Process(void){
	//make device discoverable
	if(connected){
		SetConnectable();
	}
	FitnessControllerDataFlag_t DataFlag = FitnessControllerUpdateState(&FitnessController);
    if(DataFlag == FC_NewDataAvailable){
    	SendHIDData();
    }
	hci_user_evt_proc();
}

void FitnessControllerHardwareInit(FitnessControllerHandle_t *FitnessController){
	ControllerButtonInit(FitnessController);
	ControllerTriggerInit(FitnessController);
	ControllerStickInit(FitnessController);
}

FitnessControllerDataFlag_t FitnessControllerUpdateState(FitnessControllerHandle_t *FitnessController){
	FitnessControllerDataFlag_t ReturnStatus = FC_NoDataAvailable;
    for(uint8_t i = 0; i < NUMBER_OF_BUTTONS; i++){
    	if(ButtonRead(&FitnessController->Buttons[i].Button) == ButtonChanged){
    		ReturnStatus |= FC_NewDataAvailable;
            if(FitnessController->Buttons[i].Button.State == ButtonPressed){
            	HIDReport.Buttons |= FitnessController->Buttons[i].ButtonMsk;
            } else {
            	HIDReport.Buttons &= ~(FitnessController->Buttons[i].ButtonMsk);
            }
    	}
    }

    for(uint8_t i = 0; i < NUMBER_OF_TRIGGERS; i++){
        if(TriggerRead(&FitnessController->Triggers[i]) == TriggerChanged){
        	ReturnStatus |= FC_NewDataAvailable;
        	HIDReport.Triggers[i] = FitnessController->Triggers[i].Position;
        }
    }

    for(uint8_t i = 0; i < NUMBER_OF_STICKS; i++){
        if(AnalogStickRead(&FitnessController->Sticks[i]) == AnalogStickChanged){
        	ReturnStatus |= FC_NewDataAvailable;
        	HIDReport.Sticks[i*2] = FitnessController->Sticks[i].X_Position;
        	HIDReport.Sticks[i*2+1] = FitnessController->Sticks[i].Y_Position;
        }
    }
    return ReturnStatus;
}

static void AddServices(void){

	  HIDServiceStatus_t HIDStatus;
	  HIDStatus = AddHIDService();
	  if(HIDStatus != HID_OK){
          printf("Add HID Service Failed\n\r");
          while(1);
	  }

	  BatteryServiceStatus_t BatStatus;
	  BatStatus = AddBatteryService();
	  if(BatStatus != Battery_OK){
		  printf("Add Battery Service Failed\n\r");
          while(1);
	  }

	  DeviceInfoServiceStatus_t DIStatus;
	  DIStatus = AddDeviceInfoService();
	  if(DIStatus != DeviceInfo_OK){
		  printf("Add Device Service Failed\n\r");
          while(1);
	  }

}

static tBleStatus SetConnectable(void){
	tBleStatus status;
    status = aci_gap_set_discoverable(ADV_IND, 0, 0, PUBLIC_ADDR, NO_WHITE_LIST_USE, sizeof(local_name), local_name, 0, NULL, 0, 0);
    connected = DEVICE_CONNECTED;
	if(status != BLE_STATUS_SUCCESS){
		printf("aci_gap_set_discoverable failed\n\r");
	}

	return status;
}

static void ControllerEventNotify(void *pData){

}

static void ControllerButtonInit(FitnessControllerHandle_t *FitnessController){
	for(uint8_t i = 0; i < NUMBER_OF_BUTTONS; i++){
		FitnessController->Buttons[i].ButtonMsk = ButtonMskLUT[i];
		if(i != XINPUT_LEFT_THUMB_INDEX && i != XINPUT_RIGHT_THUMB_INDEX){
		    ButtonInit(i, &FitnessController->Buttons[i].Button, ButtonIO_DriverPosLogic);
		} else {
			ButtonInit(i, &FitnessController->Buttons[i].Button, ButtonIO_DriverNegLogic);
		}
	}

}

static void ControllerTriggerInit(FitnessControllerHandle_t *FitnessController){
	TriggerInit(&FitnessController->Triggers[XINPUT_LEFTANALOG_INDEX], TriggerIO_Driver1);
	TriggerInit(&FitnessController->Triggers[XINPUT_RIGHTANALOG_INDEX], TriggerIO_Driver2);
}

static void ControllerStickInit(FitnessControllerHandle_t *FitnessController){
   AnalogStickInit(&FitnessController->Sticks[XINPUT_LEFTANALOG_INDEX], AnalogStickIO_Driver1);
   AnalogStickInit(&FitnessController->Sticks[XINPUT_RIGHTANALOG_INDEX], AnalogStickIO_Driver2);
}
