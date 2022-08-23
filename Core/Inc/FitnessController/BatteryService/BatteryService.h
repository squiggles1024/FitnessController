/*
 * BatteryService.h
 *
 *  Created on: Jul 13, 2022
 *      Author: evanl
 */

#ifndef INC_FITNESSCONTROLLER_BATTERYSERVICE_BATTERYSERVICE_H_
#define INC_FITNESSCONTROLLER_BATTERYSERVICE_BATTERYSERVICE_H_
#include <stdint.h>

typedef enum{
     Battery_LevelCharErr,
	 Battery_AddServiceErr,
	 Battery_UpdateCharErr,
	 Battery_OK
}BatteryServiceStatus_t;

BatteryServiceStatus_t AddBatteryService(void);

uint16_t GetBatteryServiceHandle(void);

#endif /* INC_FITNESSCONTROLLER_BATTERYSERVICE_BATTERYSERVICE_H_ */
