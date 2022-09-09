/*
 * dpad.h
 *
 *  Created on: Sep 7, 2022
 *      Author: evanl
 */

#ifndef INC_FITNESSCONTROLLER_CONTROLLER_PARTS_DPAD_H_
#define INC_FITNESSCONTROLLER_CONTROLLER_PARTS_DPAD_H_
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "dpad_hardware.h"
#include <stdint.h>

/**************************************//**************************************//**************************************
 * Enums
 **************************************//**************************************//**************************************/
typedef enum{
	DpadChanged = 0,
	DpadUnchanged,
	DpadErr
}DpadStatus_t;

/**************************************//**************************************//**************************************
 * Driver Structs
 **************************************//**************************************//**************************************/
typedef uint8_t DpadIDNumber_t;

typedef struct{
	DpadIDNumber_t DpadIDNumber;
    HatSwitchState_t State;
    HatSwitch_IO_Drv_t IO_Driver;
}Dpad_Handle_t;

/**************************************//**************************************//**************************************
 * Public Function Declarations
 **************************************//**************************************//**************************************/
void DpadInit(DpadIDNumber_t DpadID, Dpad_Handle_t *Dpad, HatSwitch_IO_Drv_t IO);
DpadStatus_t DpadRead(Dpad_Handle_t *Dpad);




#endif /* INC_FITNESSCONTROLLER_CONTROLLER_PARTS_DPAD_H_ */
