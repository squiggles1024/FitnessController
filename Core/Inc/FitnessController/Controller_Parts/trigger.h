/*
 * trigger.h
 *
 *  Created on: Aug 22, 2022
 *      Author: evanl
 */

#ifndef INC_FITNESSCONTROLLER_CONTROLLER_PARTS_TRIGGER_H_
#define INC_FITNESSCONTROLLER_CONTROLLER_PARTS_TRIGGER_H_
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "trigger_hardware.h"
#include <stdint.h>

/**************************************//**************************************//**************************************
 * Enums
 **************************************//**************************************//**************************************/
#define NUMBER_OF_TRIGGERS (2U)


typedef enum{
	TriggerChanged = 0,
	TriggerUnchanged,
	TriggerErr
}TriggerStatus_t;

/**************************************//**************************************//**************************************
 * Driver Structs
 **************************************//**************************************//**************************************/

typedef struct{
    uint8_t Position;
    Trigger_IO_Drv_t IO_Driver;
}Trigger_Handle_t;

/**************************************//**************************************//**************************************
 * Public Function Declarations
 **************************************//**************************************//**************************************/
void TriggerInit(Trigger_Handle_t *Trigger, Trigger_IO_Drv_t IO);
TriggerStatus_t TriggerRead(Trigger_Handle_t *Trigger);




#endif /* INC_FITNESSCONTROLLER_CONTROLLER_PARTS_TRIGGER_H_ */
