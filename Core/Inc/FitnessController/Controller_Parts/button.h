/*
 * button.h
 *
 *  Created on: Aug 22, 2022
 *      Author: evanl
 */

#ifndef INC_FITNESSCONTROLLER_CONTROLLER_PARTS_BUTTON_H_
#define INC_FITNESSCONTROLLER_CONTROLLER_PARTS_BUTTON_H_
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "button_hardware.h"
#include <stdint.h>

/**************************************//**************************************//**************************************
 * Enums
 **************************************//**************************************//**************************************/
typedef enum{
	ButtonChanged = 0,
	ButtonUnchanged,
	ButtonErr
}ButtonStatus_t;

/**************************************//**************************************//**************************************
 * Driver Structs
 **************************************//**************************************//**************************************/
typedef uint8_t ButtonIDNumber_t;

typedef struct{
	ButtonIDNumber_t ButtonIDNumber;
    ButtonState_t State;
    Button_IO_Drv_t IO_Driver;
}Button_Handle_t;

/**************************************//**************************************//**************************************
 * Public Function Declarations
 **************************************//**************************************//**************************************/
void ButtonInit(ButtonIDNumber_t ButtonID, Button_Handle_t *Button, Button_IO_Drv_t IO);
ButtonStatus_t ButtonRead(Button_Handle_t *Button);



#endif /* INC_FITNESSCONTROLLER_CONTROLLER_PARTS_BUTTON_H_ */
