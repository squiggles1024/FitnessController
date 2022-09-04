/*
 * analog_stick.h
 *
 *  Created on: Aug 22, 2022
 *      Author: evanl
 */

#ifndef INC_FITNESSCONTROLLER_CONTROLLER_PARTS_ANALOG_STICK_H_
#define INC_FITNESSCONTROLLER_CONTROLLER_PARTS_ANALOG_STICK_H_
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "analog_stick_hardware.h"
#include <stdint.h>

/**************************************//**************************************//**************************************
 * Enums
 **************************************//**************************************//**************************************/
#define NUMBER_OF_STICKS (2U)

typedef enum{
	AnalogStickChanged = 0,
	AnalogStickUnchanged,
	AnalogStickErr
}AnalogStickStatus_t;

/**************************************//**************************************//**************************************
 * Driver Structs
 **************************************//**************************************//**************************************/

typedef struct{
    int16_t X_Position;
    int16_t Y_Position;
    AnalogStick_IO_Drv_t IO_Driver;
}AnalogStick_Handle_t;

/**************************************//**************************************//**************************************
 * Public Function Declarations
 **************************************//**************************************//**************************************/
void AnalogStickInit(AnalogStick_Handle_t *AnalogStick, AnalogStick_IO_Drv_t IO);
AnalogStickStatus_t AnalogStickRead(AnalogStick_Handle_t *AnalogStick);


#endif /* INC_FITNESSCONTROLLER_CONTROLLER_PARTS_ANALOG_STICK_H_ */
