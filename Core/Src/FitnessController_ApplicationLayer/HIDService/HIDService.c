/*
 * HIDService.c
 *
 *  Created on: Jul 13, 2022
 *      Author: evanl
 */

#include "HIDService.h"
#include <stdint.h>
#include <stdio.h>
#include "bluenrg_utils.h"
#include "bluenrg_conf.h"
#include "hci.h"
#include "bluenrg_types.h"
#include "bluenrg_gap.h"
#include "bluenrg_aci.h"
#include "hci_le.h"
#include "HID.h"


#define HID_SERVICE_CHAR_QTY (0x4)

#define HID_INFO_INDEX              (0x0)
#define HID_REPORTMAP_INDEX         (0x1)
#define HID_CONTROLPT_INDEX         (0x2)
#define HID_REPORT_INDEX            (0x3)

#define MAX_VALUELEN_PAYLOAD_SIZE (117)

#define HID_INFO_UUID_TYPE              (UUID_TYPE_16)
#define HID_REPORTMAP_UUID_TYPE         (UUID_TYPE_16)
#define HID_CONTROLPT_UUID_TYPE         (UUID_TYPE_16)
#define HID_REPORT_UUID_TYPE            (UUID_TYPE_16)

//#define HID_SERVICE_UUID       (0x1809) //Health Thermometer for debug purposes.
#define HID_SERVICE_UUID       (0x1812)
#define HID_INFO_UUID          (0x2A4A)
#define HID_REPORTMAP_UUID     (0x2A4B)
#define HID_CONTROLPT_UUID     (0x2A4C)
#define HID_REPORT_UUID        (0x2A4D)


#define HID_REPORTREF_DESC_UUID   (0x2908)


#define HID_INFO_VALUELEN            (sizeof(HIDInfoValue))
#define HID_REPORTMAP_VALUELEN       (sizeof(HID_ReportMap))
#define HID_CONTROLPT_VALUELEN       (sizeof(HIDControlPoint_t))
#define HID_REPORT_VALUELEN          (sizeof(HIDReportChar_t))


#define HID_INFO_PROP          (CHAR_PROP_READ)
#define HID_REPORTMAP_PROP     (CHAR_PROP_READ)
#define HID_CONTROLPT_PROP     (CHAR_PROP_WRITE_WITHOUT_RESP)
#define HID_REPORT_PROP        (CHAR_PROP_READ | CHAR_PROP_NOTIFY)


#define HID_INFO_PERM          (ATTR_PERMISSION_NONE)
#define HID_REPORTMAP_PERM     (ATTR_PERMISSION_NONE)
#define HID_CONTROLPT_PERM     (ATTR_PERMISSION_NONE)
#define HID_REPORT_PERM        (ATTR_PERMISSION_NONE)


#define HID_INFO_NOTIFYMODE          (GATT_DONT_NOTIFY_EVENTS)
#define HID_REPORTMAP_NOTIFYMODE     (GATT_DONT_NOTIFY_EVENTS)
#define HID_CONTROLPT_NOTIFYMODE     (GATT_NOTIFY_ATTRIBUTE_WRITE)
#define HID_REPORT_NOTIFYMODE        (GATT_DONT_NOTIFY_EVENTS)


#define HID_INFO_ERRSTRING           "HID Info Characteristic Error\n\r"
#define HID_REPORTMAP_ERRSTRING      "HID Report Map Characteristic Error\n\r"
#define HID_CONTROLPT_ERRSTRING      "HID Control Point Characteristic Error\n\r"
#define HID_REPORT_ERRSTRING         "HID Report Characteristic Error\n\r"


#define HID_INFO_ERR_RETURN          HID_InfoCharErr
#define HID_REPORTMAP_ERR_RETURN     HID_ReportMapCharErr
#define HID_CONTROLPT_ERR_RETURN     HID_ControlPtCharErr
#define HID_REPORT_ERR_RETURN        HID_ReportCharErr





static uint16_t HidServiceHandle;
static uint16_t HIDCharHandleLookUpTable[HID_SERVICE_CHAR_QTY];
static uint16_t HIDReportDescHandle;

static const uint8_t HIDCharUUIDType[HID_SERVICE_CHAR_QTY] = {
		HID_INFO_UUID_TYPE,
		HID_REPORTMAP_UUID_TYPE,
		HID_CONTROLPT_UUID_TYPE,
		HID_REPORT_UUID_TYPE
};

static const uint16_t HIDCharUUIDLookUpTable[HID_SERVICE_CHAR_QTY] = {
		HID_INFO_UUID,
		HID_REPORTMAP_UUID,
		HID_CONTROLPT_UUID,
		HID_REPORT_UUID
};

static uint16_t HIDCharValueLenLookUpTable[HID_SERVICE_CHAR_QTY] = {
		HID_INFO_VALUELEN,
		HID_REPORTMAP_VALUELEN,
		HID_CONTROLPT_VALUELEN,
		HID_REPORT_VALUELEN
};

static uint16_t HIDCharPropertiesLookUpTable[HID_SERVICE_CHAR_QTY] = {
		HID_INFO_PROP,
		HID_REPORTMAP_PROP,
		HID_CONTROLPT_PROP,
		HID_REPORT_PROP
};

static const uint8_t HIDCharPermissionsLookUpTable[HID_SERVICE_CHAR_QTY] = {
		HID_INFO_PERM,
		HID_REPORTMAP_PERM,
		HID_CONTROLPT_PERM,
		HID_REPORT_PERM
};

static const uint8_t HID_CharNotifyModeLookUpTable[HID_SERVICE_CHAR_QTY] = {
		HID_INFO_NOTIFYMODE,
		HID_REPORTMAP_NOTIFYMODE,
		HID_CONTROLPT_NOTIFYMODE,
		HID_REPORT_NOTIFYMODE
};

static const char *HIDCharErrorStringLookUpTable[HID_SERVICE_CHAR_QTY] = {
		HID_INFO_ERRSTRING,
		HID_REPORTMAP_ERRSTRING,
		HID_CONTROLPT_ERRSTRING,
		HID_REPORT_ERRSTRING
};

static const HIDServiceStatus_t HIDCharErrorReturnLookUpTable[HID_SERVICE_CHAR_QTY] = {
		HID_INFO_ERR_RETURN,
		HID_REPORTMAP_ERR_RETURN,
		HID_CONTROLPT_ERR_RETURN,
		HID_REPORT_ERR_RETURN
};

static const void *HIDCharValueLookUpTable[HID_SERVICE_CHAR_QTY] = {
        &HIDInfoValue,
		&HID_ReportMap[0],
		&HIDControlPoint,
        &HIDReport
};

static HIDServiceStatus_t AddHIDCharacteristics(void);
static HIDServiceStatus_t InitHIDCharacteristicValues(void);

HIDServiceStatus_t AddHIDService(void){
	tBleStatus status;
	HIDServiceStatus_t ret;
	uint16_t uuid = HID_SERVICE_UUID;
	status = aci_gatt_add_serv(UUID_TYPE_16, (const uint8_t*)&uuid, PRIMARY_SERVICE, 16, &HidServiceHandle);
	if(status != BLE_STATUS_SUCCESS){
		printf("Adding HID Service Failed\n\r");
		return HID_AddServiceErr;
	}
	ret = AddHIDCharacteristics();
    return ret;

}

uint16_t GetHIDServiceHandle(void){
	return HidServiceHandle;
}

static HIDServiceStatus_t AddHIDCharacteristics(void){
	tBleStatus status;
	HIDServiceStatus_t ret;
    for(uint8_t i = HID_INFO_INDEX; i < HID_SERVICE_CHAR_QTY; i++){
        status = aci_gatt_add_char(HidServiceHandle,                            //Service Handle
        		                   HIDCharUUIDType[i],                          //UUID Type
				                   (const uint8_t*)&HIDCharUUIDLookUpTable[i],  //UUID Value
								   HIDCharValueLenLookUpTable[i],               //Char Value Length
				                   HIDCharPropertiesLookUpTable[i],             //Char Properties
				                   HIDCharPermissionsLookUpTable[i],            //Char SecPermissions
								   HID_CharNotifyModeLookUpTable[i],            //Char Application (Server Side)Notify Mode e.g. Will the BLE Controller Notify me when a r/w occurs
				                   16,                                          //Encyption Key Size
				                   0,                                           //Does the value field have variable length? 1= yes, 0 = no
				                   &HIDCharHandleLookUpTable[i]);               //HID Char Handle Address
        if(status != BLE_STATUS_SUCCESS){
        	printf(HIDCharErrorStringLookUpTable[i]);
        	return HIDCharErrorReturnLookUpTable[i];
        }
    }
    ret = InitHIDCharacteristicValues();
    return ret;
}

static HIDServiceStatus_t InitHIDCharacteristicValues(void){
	tBleStatus status;

	for(uint8_t i = HID_INFO_INDEX; i < HID_SERVICE_CHAR_QTY; i++){
		status = aci_gatt_update_char_value_ext_IDB05A1(HidServiceHandle,              //Handle of the service to which the characteristic belongs.
							                            HIDCharHandleLookUpTable[i],       //Handle of the characteristic.
														NOTIFICATION,                      //The offset from which the attribute value has to be updated
														0,
														0,
														HIDCharValueLenLookUpTable[i],     //Length of the value to be updated
														HIDCharValueLookUpTable[i]);       //Updated characteristic value


        if(status != BLE_STATUS_SUCCESS){
        	printf("Error Initializing Characteristic\n\r");
        	printf(HIDCharErrorStringLookUpTable[i]);
        	return HIDCharErrorReturnLookUpTable[i];
        }
        if(i == HID_REPORT_INDEX){
        	 uint16_t desc_uuid = HID_REPORTREF_DESC_UUID;
             status = aci_gatt_add_char_desc(HidServiceHandle,
            		                         HIDCharHandleLookUpTable[HID_REPORT_INDEX],
											 UUID_TYPE_16 ,
											 (const uint8_t*)&desc_uuid,
											 sizeof(ReportRefDesc),
											 sizeof(ReportRefDesc),
											 (const void*)&ReportRefDesc,
											 ATTR_PERMISSION_NONE,
											 ATTR_ACCESS_READ_ONLY,
											 GATT_DONT_NOTIFY_EVENTS ,
											 7,
											 0,
											 &HIDReportDescHandle);
        }
	}
	return HID_OK;
}

void SendHIDData(void){
	aci_gatt_update_char_value_ext_IDB05A1(     HidServiceHandle,                                     //Handle of the service to which the characteristic belongs.
					                            HIDCharHandleLookUpTable[HID_REPORT_INDEX],       //Handle of the characteristic.
												NOTIFICATION,                                                //The offset from which the attribute value has to be updated
												0,
												0,
												HIDCharValueLenLookUpTable[HID_REPORT_INDEX],     //Length of the value to be updated
												HIDCharValueLookUpTable[HID_REPORT_INDEX]);       //Updated characteristic value

}



