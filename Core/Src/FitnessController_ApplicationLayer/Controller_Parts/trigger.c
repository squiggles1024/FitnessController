/*
 * trigger.c
 *
 *  Created on: Aug 22, 2022
 *      Author: evanl
 */
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "trigger.h"

/**************************************//**************************************//**************************************
 * Public Function Definitions
 **************************************//**************************************//**************************************/
/**************************************//**************************************
 *@Brief: Initializes a Trigger handle
 *@Params: Init struct with desired user settings, Trigger handle to initialize, Low level IO Driver
 *@Return: None
 *@Precondition: None
 *@Postcondition: Trigger handle and low level hardware will be initialized and ready to use.
 **************************************//**************************************/
void TriggerInit(Trigger_Handle_t *Trigger, Trigger_IO_Drv_t IO){
	Trigger->IO_Driver = IO;
	Trigger->IO_Driver.init();
	Trigger->Position = 0;
}

/**************************************//**************************************
 *@Brief: Updates Trigger Position and Raw X/Y Coordinate
 *@Params: Trigger Handle
 *@Return: TriggerChanged if previous position != new position. Uses XPosRaw/YPosRaw in analog mode
 *@Precondition: TriggerHandle must be initialized
 *@Postcondition: Trigger XPosRaw/YPosRaw/State will be updated.
 **************************************//**************************************/
TriggerStatus_t TriggerRead(Trigger_Handle_t *Trigger){
	uint8_t Previous = Trigger->Position;
	Trigger->IO_Driver.read(&(Trigger->Position));
    if((Trigger->Position == 0 && Previous == 0)){
        return TriggerUnchanged;
	}
    return TriggerChanged;
}



