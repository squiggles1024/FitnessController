/*
 * dpad.c
 *
 *  Created on: Sep 7, 2022
 *      Author: evanl
 */
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "dpad.h"

/**************************************//**************************************//**************************************
 * Public Function Definitions
 **************************************//**************************************//**************************************/
/**************************************//**************************************
 *@Brief: Initializes a Dpad Device Handle
 *@Params: Init struct with settings, Handle to initialized, low level IO driver
 *@Return: None
 *@Precondition: None
 *@Postcondition: Dpad handle will be initialized and ready to use
 **************************************//**************************************/
void DpadInit(DpadIDNumber_t DpadID, Dpad_Handle_t *Dpad, HatSwitch_IO_Drv_t IO){
	Dpad->IO_Driver   = IO;
	Dpad->IO_Driver.init();
	Dpad->DpadIDNumber = DpadID;
	Dpad->State = HatNeutral;
}

/**************************************//**************************************
 *@Brief: Updates the state of a Dpad
 *@Params: Dpad handle to read
 *@Return: DpadChanged if the Dpad changed states, otherwise DpadUnchanged
 *@Precondition: DpadHandle should be initialized/
 *@Postcondition: DpadState in the DpadHandle will be updated.
 **************************************//**************************************/
DpadStatus_t DpadRead(Dpad_Handle_t *Dpad){
    HatSwitchState_t Previous_State = Dpad->State;
    Dpad->State = Dpad->IO_Driver.read(Dpad->DpadIDNumber);
    if(Previous_State != Dpad->State){
    	return DpadChanged;
    } else {
    	return DpadUnchanged;
    }
}

