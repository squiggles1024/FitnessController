/*
 * analog_stick.c
 *
 *  Created on: Aug 22, 2022
 *      Author: evanl
 */
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "analog_stick.h"

/**************************************//**************************************//**************************************
 * Public Function Definitions
 **************************************//**************************************//**************************************/
/**************************************//**************************************
 *@Brief: Initializes a AnalogStick handle
 *@Params: Init struct with desired user settings, AnalogStick handle to initialize, Low level IO Driver
 *@Return: None
 *@Precondition: None
 *@Postcondition: AnalogStick handle and low level hardware will be initialized and ready to use.
 **************************************//**************************************/
void AnalogStickInit(AnalogStick_Handle_t *AnalogStick, AnalogStick_IO_Drv_t IO){
	AnalogStick->IO_Driver = IO;
	AnalogStick->IO_Driver.init();
	AnalogStick->X_Position = 0;
	AnalogStick->Y_Position = 0;
}

/**************************************//**************************************
 *@Brief: Updates AnalogStick Position and Raw X/Y Coordinate
 *@Params: AnalogStick Handle
 *@Return: AnalogStickChanged if previous position != new position. Uses XPosRaw/YPosRaw in analog mode
 *@Precondition: AnalogStickHandle must be initialized
 *@Postcondition: AnalogStick XPosRaw/YPosRaw/State will be updated.
 **************************************//**************************************/
AnalogStickStatus_t AnalogStickRead(AnalogStick_Handle_t *AnalogStick){
	int16_t PreviousX = AnalogStick->X_Position;
	int16_t PreviousY = AnalogStick->Y_Position;
	AnalogStick->IO_Driver.read(&(AnalogStick->X_Position), &(AnalogStick->Y_Position));
    if((AnalogStick->X_Position == 0 && PreviousX == 0) && (AnalogStick->Y_Position == 0 && PreviousY == 0)){
        return AnalogStickUnchanged;
	}
    return AnalogStickChanged;
}


