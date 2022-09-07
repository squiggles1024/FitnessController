/*
 * DeviceInfoService.h
 *
 *  Created on: Jul 13, 2022
 *      Author: evanl
 */

#ifndef INC_FITNESSCONTROLLER_DEVICEINFOSERVICE_DEVICEINFOSERVICE_H_
#define INC_FITNESSCONTROLLER_DEVICEINFOSERVICE_DEVICEINFOSERVICE_H_
#include <stdint.h>

typedef enum{
     DeviceInfo_InfoCharErr,
	 DeviceInfo_AddServiceErr,
	 DeviceInfo_MfgNameCharErr,
	 DeviceInfo_ModelNumCharErr,
	 DeviceInfo_SerialNumCharErr,
	 DeviceInfo_HardwareRevCharErr,
	 DeviceInfo_PnPIDCharErr,
	 DeviceInfo_OK
}DeviceInfoServiceStatus_t;

DeviceInfoServiceStatus_t AddDeviceInfoService(void);

uint16_t GetDeviceInfoServiceHandle(void);

#endif /* INC_FITNESSCONTROLLER_DEVICEINFOSERVICE_DEVICEINFOSERVICE_H_ */
