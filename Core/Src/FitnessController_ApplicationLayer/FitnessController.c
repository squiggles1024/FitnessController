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

#define DEVICE_CONNECTABLE (1)
#define DEVICE_CONNECTED (0)

static const uint8_t SERVER_BDADDR[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
static const char local_name[] = {AD_TYPE_COMPLETE_LOCAL_NAME,'F', 'i', 't', 'n', 'e','s','s',' ','C','o','n','t','r','o','l','l','e','r'};
static uint8_t connected = DEVICE_CONNECTABLE;
static void AddServices(void);
static tBleStatus SetConnectable(void);
static void ControllerEventNotify(void *pData);



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
	//update controller
    //if new controller data is available:
	//call SendHIDData();
	hci_user_evt_proc();
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

