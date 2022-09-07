/*
 * DeviceInfoService.c
 *
 *  Created on: Jul 13, 2022
 *      Author: evanl
 */

#include "DeviceInfoService.h"
#include "bluenrg_utils.h"
#include "bluenrg_conf.h"
#include "hci.h"
#include "bluenrg_types.h"
#include "bluenrg_gap.h"
#include "bluenrg_aci.h"
#include "hci_le.h"
#include <stdio.h>

/*
typedef struct{
    uint8_t VIDSource;
    uint16_t VID;
    uint16_t PID;
    uint16_t Rev;
}__attribute__((packed)) PnP_ID_t;
*/
//Number of Characteristics in the service
#define DEVICEINFO_SERVICE_CHAR_QTY  (0x4)
//Index of the service in the look up tables
#define DEVICEINFO_MFGNAME_INDEX     (0x0)
#define DEVICEINFO_MODELNUM_INDEX    (0x1)
#define DEVICEINFO_SERIALNUM_INDEX   (0x2)
#define DEVICEINFO_HARDWAREREV_INDEX (0x3)
//#define DEVICEINFO_PNPID_INDEX (0x04)

//UUID For Device Info
#define DEVICEINFO_SERVICE_UUID       (0x180A)

//UUIDs for the Characteristics
#define DEVICEINFO_MFGNAME_UUID         (0x2A29)
#define DEVICEINFO_MODELNUM_UUID        (0x2A24)
#define DEVICEINFO_SERIALNUM_UUID       (0x2A25)
#define DEVICEINFO_HARDWAREREV_UUID     (0x2A27)
//#define DEVICEINFO_PNPID_UUID           (0x2A50)

#define DEVICEINFO_MFGNAME_UUIDTYPE                (UUID_TYPE_16)
#define DEVICEINFO_MODELNUM_UUIDTYPE               (UUID_TYPE_16)
#define DEVICEINFO_SERIALNUM_UUIDTYPE              (UUID_TYPE_16)
#define DEVICEINFO_HARDWAREREV_UUIDTYPE            (UUID_TYPE_16)
//#define DEVICEINFO_PNPID_UUIDTYPE                  (UUID_TYPE_16)

//Values for the String Characteristics
static const char DEVICEINFO_MFGNAME_STR[]      = "Evan Lemson";
static const char DEVICEINFO_MODELNUMBER_STR[]  = "Model 1.0.0";
static const char DEVICEINFO_SERIALNUMBER_STR[] = "23478905A";
static const char DEVICEINFO_HARDWAREREV_STR[]  = "b_l475e_iot01a1";
/*
static const PnP_ID_t PNP_ID = {
		.VIDSource = 0x02,
		.VID = 0x045E,
		.PID = 0x028E,
		.Rev = 0x0114
};
*/

#define DEVICEINFO_MFGNAME_VALUELEN                (sizeof(DEVICEINFO_MFGNAME_STR))
#define DEVICEINFO_MODELNUM_VALUELEN               (sizeof(DEVICEINFO_MODELNUMBER_STR))
#define DEVICEINFO_SERIALNUM_VALUELEN              (sizeof(DEVICEINFO_SERIALNUMBER_STR))
#define DEVICEINFO_HARDWAREREV_VALUELEN            (sizeof(DEVICEINFO_HARDWAREREV_STR))
//#define DEVICEINFO_PNPID_VALUELEN                  (sizeof(PNP_ID))

#define DEVICEINFO_MFGNAME_PROP                    (CHAR_PROP_READ)
#define DEVICEINFO_MODELNUM_PROP                   (CHAR_PROP_READ)
#define DEVICEINFO_SERIALNUM_PROP                  (CHAR_PROP_READ)
#define DEVICEINFO_HARDWAREREV_PROP                (CHAR_PROP_READ)
//#define DEVICEINFO_PNPID_PROP                      (CHAR_PROP_READ)

#define DEVICEINFO_MFGNAME_PERM                    (ATTR_PERMISSION_NONE)
#define DEVICEINFO_MODELNUM_PERM                   (ATTR_PERMISSION_NONE)
#define DEVICEINFO_SERIALNUM_PERM                  (ATTR_PERMISSION_NONE)
#define DEVICEINFO_HARDWAREREV_PERM                (ATTR_PERMISSION_NONE)
//#define DEVICEINFO_PNPID_PERM                      (ATTR_PERMISSION_NONE)

#define DEVICEINFO_MFGNAME_NOTIFYMODE            (GATT_DONT_NOTIFY_EVENTS)
#define DEVICEINFO_MODELNUM_NOTIFYMODE           (GATT_DONT_NOTIFY_EVENTS)
#define DEVICEINFO_SERIALNUM_NOTIFYMODE          (GATT_DONT_NOTIFY_EVENTS)
#define DEVICEINFO_HARDWAREREV_NOTIFYMODE        (GATT_DONT_NOTIFY_EVENTS)
//#define DEVICEINFO_PNPID_NOTIFYMODE              (GATT_DONT_NOTIFY_EVENTS)

#define DEVICEINFO_MFGNAME_ERRSTRING             "Device Info Mfg Name Characteristic Error\n\r"
#define DEVICEINFO_MODELNUM_ERRSTRING            "Device Info Model Number Characteristic Error\n\r"
#define DEVICEINFO_SERIALNUM_ERRSTRING           "Device Info Serial Number Characteristic Error\n\r"
#define DEVICEINFO_HARDWAREREV_ERRSTRING         "Device Info Hardware Revision Characteristic Error\n\r"
//#define DEVICEINFO_PNPID_ERRSTRING               "Device Info PnP ID Characteristic Error\n\r"

#define DEVICEINFO_MFGNAME_ERR_RETURN             DeviceInfo_MfgNameCharErr
#define DEVICEINFO_MODELNUM_ERR_RETURN            DeviceInfo_ModelNumCharErr
#define DEVICEINFO_SERIALNUM_ERR_RETURN           DeviceInfo_SerialNumCharErr
#define DEVICEINFO_HARDWAREREV_ERR_RETURN         DeviceInfo_HardwareRevCharErr
//#define DEVICEINFO_PNPID_ERR_RETURN               DeviceInfo_PnPIDCharErr

static uint16_t DeviceInfoServiceHandle;
static uint16_t DeviceInfoCharHandleLookUpTable[DEVICEINFO_SERVICE_CHAR_QTY];

static const uint8_t DeviceInfoCharUUIDTypeLookUpTable[DEVICEINFO_SERVICE_CHAR_QTY] = {
		DEVICEINFO_MFGNAME_UUIDTYPE,
		DEVICEINFO_MODELNUM_UUIDTYPE,
		DEVICEINFO_SERIALNUM_UUIDTYPE,
		DEVICEINFO_HARDWAREREV_UUIDTYPE,
		//DEVICEINFO_PNPID_UUIDTYPE
};

static const uint16_t DeviceInfoCharUUIDLookUpTable[DEVICEINFO_SERVICE_CHAR_QTY] = {
		DEVICEINFO_MFGNAME_UUID,
		DEVICEINFO_MODELNUM_UUID,
		DEVICEINFO_SERIALNUM_UUID,
		DEVICEINFO_HARDWAREREV_UUID,
		//DEVICEINFO_PNPID_UUID
};

static uint8_t DeviceInfoCharValueLengthLookUpTable[DEVICEINFO_SERVICE_CHAR_QTY] = {
		DEVICEINFO_MFGNAME_VALUELEN,
		DEVICEINFO_MODELNUM_VALUELEN,
		DEVICEINFO_SERIALNUM_VALUELEN,
		DEVICEINFO_HARDWAREREV_VALUELEN,
		//DEVICEINFO_PNPID_VALUELEN
};

static uint8_t DeviceInfo_CharPropertiesLookUpTable[DEVICEINFO_SERVICE_CHAR_QTY] = {
		DEVICEINFO_MFGNAME_PROP,
		DEVICEINFO_MODELNUM_PROP,
		DEVICEINFO_SERIALNUM_PROP,
		DEVICEINFO_HARDWAREREV_PROP,
		//DEVICEINFO_PNPID_PROP
};

static const uint8_t DeviceInfoCharPermissionsLookUpTable[DEVICEINFO_SERVICE_CHAR_QTY] = {
		DEVICEINFO_MFGNAME_PERM,
		DEVICEINFO_MODELNUM_PERM,
		DEVICEINFO_SERIALNUM_PERM,
		DEVICEINFO_HARDWAREREV_PERM,
		//DEVICEINFO_PNPID_PERM
};

static const uint8_t DeviceInfoCharNotifyModeLookUpTable[DEVICEINFO_SERVICE_CHAR_QTY] = {
		DEVICEINFO_MFGNAME_NOTIFYMODE,
		DEVICEINFO_MODELNUM_NOTIFYMODE,
		DEVICEINFO_SERIALNUM_NOTIFYMODE,
		DEVICEINFO_HARDWAREREV_NOTIFYMODE,
		//DEVICEINFO_PNPID_NOTIFYMODE
};

//Look up table containing the above string characteristics
static const void* DeviceInfoCharValueStrings[DEVICEINFO_SERVICE_CHAR_QTY] = {
		DEVICEINFO_MFGNAME_STR,
		DEVICEINFO_MODELNUMBER_STR,
		DEVICEINFO_SERIALNUMBER_STR,
		DEVICEINFO_HARDWAREREV_STR,
		//&PNP_ID
};

static const char *DeviceInfoCharErrorStringLookUpTable[DEVICEINFO_SERVICE_CHAR_QTY] = {
		DEVICEINFO_MFGNAME_ERRSTRING,
		DEVICEINFO_MODELNUM_ERRSTRING,
		DEVICEINFO_SERIALNUM_ERRSTRING,
		DEVICEINFO_HARDWAREREV_ERRSTRING,
		//DEVICEINFO_PNPID_ERRSTRING
};

static const DeviceInfoServiceStatus_t DeviceInfoCharErrorReturnLookUpTable[DEVICEINFO_SERVICE_CHAR_QTY] = {
		DeviceInfo_MfgNameCharErr,
		DeviceInfo_ModelNumCharErr,
		DeviceInfo_SerialNumCharErr,
		DeviceInfo_HardwareRevCharErr,
		//DeviceInfo_PnPIDCharErr
};


static DeviceInfoServiceStatus_t AddDeviceInfoCharacteristics(void);


DeviceInfoServiceStatus_t AddDeviceInfoService(void){
	tBleStatus status;
	DeviceInfoServiceStatus_t ret;
	uint16_t uuid = DEVICEINFO_SERVICE_UUID;
	status = aci_gatt_add_serv(UUID_TYPE_16, (const uint8_t*)&uuid, PRIMARY_SERVICE, 16, &DeviceInfoServiceHandle);
	if(status != BLE_STATUS_SUCCESS){
		printf("Adding Device Info Service Failed\n\r");
		return DeviceInfo_AddServiceErr;
	}
	ret = AddDeviceInfoCharacteristics();
    return ret;

}

uint16_t GetDeviceInfoServiceHandle(void){
	return DeviceInfoServiceHandle;
}

static DeviceInfoServiceStatus_t InitDeviceInfoCharacteristics(void){
	tBleStatus status;
    for(uint8_t i = DEVICEINFO_MFGNAME_INDEX; i < DEVICEINFO_SERVICE_CHAR_QTY; i++){
    	status = aci_gatt_update_char_value(DeviceInfoServiceHandle, DeviceInfoCharHandleLookUpTable[i], 0, DeviceInfoCharValueLengthLookUpTable[i], DeviceInfoCharValueStrings[i]);
    	if(status != BLE_STATUS_SUCCESS){
    		printf(DeviceInfoCharErrorStringLookUpTable[i]);
    		printf("Fail on Init Device Info with return code %u",status);
    		return DeviceInfoCharErrorReturnLookUpTable[i];
    	}
    }
    return DeviceInfo_OK;
}


static DeviceInfoServiceStatus_t AddDeviceInfoCharacteristics(void){
	tBleStatus status;
    for(uint8_t i = DEVICEINFO_MFGNAME_INDEX; i < DEVICEINFO_SERVICE_CHAR_QTY; i++){
        status = aci_gatt_add_char(DeviceInfoServiceHandle,                            //Service Handle
        		                   DeviceInfoCharUUIDTypeLookUpTable[i],               //UUID Type
				                   (const uint8_t*)&DeviceInfoCharUUIDLookUpTable[i],  //UUID Value
				                   DeviceInfoCharValueLengthLookUpTable[i],            //Char Value Length
				                   DeviceInfo_CharPropertiesLookUpTable[i],            //Char Properties
				                   DeviceInfoCharPermissionsLookUpTable[i],            //Char SecPermissions
								   DeviceInfoCharNotifyModeLookUpTable[i],             //Char Application Notify Mode
				                   16,                                                 //Encryption Key Size
				                   1,                                                  //variable length value field (1) or not (0).
				                   &DeviceInfoCharHandleLookUpTable[i]);               //DeviceInfo Char Handle Address
        if(status != BLE_STATUS_SUCCESS){
        	printf(DeviceInfoCharErrorStringLookUpTable[i]);
        	return DeviceInfoCharErrorReturnLookUpTable[i];
        }
    }
    return InitDeviceInfoCharacteristics();
}

