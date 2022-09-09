/*
 * FitnessController.h
 *
 *  Created on: Jul 11, 2022
 *      Author: evanl
 */

#ifndef INC_FITNESSCONTROLLER_FITNESSCONTROLLER_H_
#define INC_FITNESSCONTROLLER_FITNESSCONTROLLER_H_
#include "b_l475e_iot01a1_conf.h"
#include "button.h"
#include "trigger.h"
#include "analog_stick.h"
#include "dpad.h"
#include "MAX30102.h"

typedef enum{
	FC_NoDataAvailable,
	FC_NewDataAvailable
}FitnessControllerDataFlag_t;

typedef struct{
	Button_Handle_t Button;
	uint16_t ButtonMsk;
}ControllerButton_t;

typedef struct{
    Dpad_Handle_t Dpad;
	ControllerButton_t Buttons[NUMBER_OF_BUTTONS];
	Trigger_Handle_t Triggers[NUMBER_OF_TRIGGERS];
	AnalogStick_Handle_t Sticks[NUMBER_OF_STICKS];
}FitnessControllerHandle_t;

extern FitnessControllerHandle_t FitnessController;

void FitnessControllerHardwareInit(FitnessControllerHandle_t *FitnessController);
FitnessControllerDataFlag_t FitnessControllerUpdateState(FitnessControllerHandle_t *FitnessController);
void FitnessControllerBLEInit(void);
void FitnessController_BLE_Process(void);

extern MAX30102_Handle_t HeartRateMonitor;

#endif /* INC_FITNESSCONTROLLER_FITNESSCONTROLLER_H_ */
