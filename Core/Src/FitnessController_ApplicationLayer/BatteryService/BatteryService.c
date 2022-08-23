/*
 * BatteryService.c
 *
 *  Created on: Jul 13, 2022
 *      Author: evanl
 */

#include "BatteryService.h"
#include "bluenrg_utils.h"
#include "bluenrg_conf.h"
#include "hci.h"
#include "bluenrg_types.h"
#include "bluenrg_gap.h"
#include "bluenrg_aci.h"
#include "hci_le.h"
#include <stdio.h>
#include <stdint.h>

#define BATTERY_SERVICE_CHAR_QTY (0x1)
#define BATTERY_LEVEL_INDEX               (0x0)

#define BATTERY_SERVICE_UUID       (0x180F)
#define BATTERY_LEVEL_UUID         (0x2A19)

#define BATTERY_LEVEL_VALUELEN            (0x01)
#define BATTERY_LEVEL_PROP                (CHAR_PROP_READ)
#define BATTERY_LEVEL_PERM                (ATTR_PERMISSION_NONE)
#define BATTERY_LEVEL_NOTIFYMODE          (GATT_DONT_NOTIFY_EVENTS)

#define BATTERY_LEVEL_ERRSTRING           "BATTERY Level Characteristic Error\n\r"
#define BATTERY_LEVEL_ERR_RETURN          Battery_LevelCharErr



//Battery Service Handle
static uint16_t BatteryServiceHandle;

//Battery Characteristic Handle
static uint16_t BatteryCharHandleLookUpTable[BATTERY_SERVICE_CHAR_QTY];

//Battery Characteristic UUID Types
static uint8_t BatteryCharUUIDType[BATTERY_SERVICE_CHAR_QTY] = {
		UUID_TYPE_16
};
//Battery Characteristic UUID
static const uint16_t BatteryCharUUIDLookUpTable[BATTERY_SERVICE_CHAR_QTY] = {
		BATTERY_LEVEL_UUID,
};
//Battery Value length in bytes
static const uint8_t BatteryCharLengthLookUpTable[BATTERY_SERVICE_CHAR_QTY] = {
		BATTERY_LEVEL_VALUELEN
};
//Battery Characteristic Properties
static uint16_t BatteryCharPropertiesLookUpTable[BATTERY_SERVICE_CHAR_QTY] = {
		BATTERY_LEVEL_PROP,
};
//Battery Characteristic Security Permissions
static const uint8_t BatteryCharSecPermissionsLookUpTable[BATTERY_SERVICE_CHAR_QTY] = {
		BATTERY_LEVEL_PERM,
};
static const uint8_t BatteryCharNotifyModeLookUpTable[BATTERY_SERVICE_CHAR_QTY] = {
        BATTERY_LEVEL_NOTIFYMODE
};

static const char *BatteryCharErrorStringLookUpTable[BATTERY_SERVICE_CHAR_QTY] = {
		BATTERY_LEVEL_ERRSTRING,

};

static const BatteryServiceStatus_t BatteryCharErrorReturnLookUpTable[BATTERY_SERVICE_CHAR_QTY] = {
		BATTERY_LEVEL_ERR_RETURN,

};

static BatteryServiceStatus_t AddBatteryCharacteristics(void);
static BatteryServiceStatus_t InitBatteryValue(void);
static BatteryServiceStatus_t UpdateBatteryValue(void);
static uint8_t GetBatteryValue(void);


BatteryServiceStatus_t AddBatteryService(void){
	tBleStatus status;
	BatteryServiceStatus_t ret;
	uint16_t uuid = BATTERY_SERVICE_UUID;
	status = aci_gatt_add_serv(UUID_TYPE_16, (const uint8_t*)&uuid, PRIMARY_SERVICE, 7, &BatteryServiceHandle);
	if(status != BLE_STATUS_SUCCESS){
		printf("Adding BATTERY Service Failed\n\r");
		return Battery_AddServiceErr;
	}

	ret = AddBatteryCharacteristics();
	if(ret != Battery_OK){
		return ret;
	}

	ret = InitBatteryValue();
	if(ret != Battery_OK){
		return ret;
	}
    return Battery_OK;
}

uint16_t GetBatteryServiceHandle(void){
	return BatteryServiceHandle;
}

static BatteryServiceStatus_t AddBatteryCharacteristics(void){
	tBleStatus status;
    for(uint8_t i = BATTERY_LEVEL_INDEX; i < BATTERY_SERVICE_CHAR_QTY; i++){
        status = aci_gatt_add_char(BatteryServiceHandle,                            //Service Handle
        		                   BatteryCharUUIDType[i],                          //UUID Type
				                   (const uint8_t*)&BatteryCharUUIDLookUpTable[i],  //UUID Value
								   BatteryCharLengthLookUpTable[i],                 //Char Value Length
				                   BatteryCharPropertiesLookUpTable[i],             //Char Properties
				                   BatteryCharSecPermissionsLookUpTable[i],         //Char SecPermissions
								   BatteryCharNotifyModeLookUpTable[i],             //Char Application Notify Mode
				                   16,                                              //Encyption Key Size
				                   0,                                               //Does the value field have variable length? 1= yes, 0 = no
				                   &BatteryCharHandleLookUpTable[i]);               //BATTERY Char Handle Address
        if(status != BLE_STATUS_SUCCESS){
        	printf(BatteryCharErrorStringLookUpTable[i]);
        	return BatteryCharErrorReturnLookUpTable[i];
        }
    }

    return Battery_OK;
}

static BatteryServiceStatus_t InitBatteryValue(void){
	BatteryServiceStatus_t ret;
	ret = UpdateBatteryValue();
	return ret;
}

static BatteryServiceStatus_t UpdateBatteryValue(){
    tBleStatus status;
    uint8_t reg = GetBatteryValue();
    status = aci_gatt_update_char_value(BatteryServiceHandle, BatteryCharHandleLookUpTable[BATTERY_LEVEL_INDEX], 0, 1, &reg);

    if(status != BLE_STATUS_SUCCESS){
    	printf("Update Battery Level char failed\n\r");
    	return Battery_UpdateCharErr;
    }

    return Battery_OK;
}

static uint8_t GetBatteryValue(void){
	return 100;
}
