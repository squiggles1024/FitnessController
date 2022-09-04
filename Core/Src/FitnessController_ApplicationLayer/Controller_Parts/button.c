/*
 * button.c
 *
 *  Created on: Aug 22, 2022
 *      Author: evanl
 */
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "Button.h"

/**************************************//**************************************//**************************************
 * Public Function Definitions
 **************************************//**************************************//**************************************/
/**************************************//**************************************
 *@Brief: Initializes a Button Device Handle
 *@Params: Init struct with settings, Handle to initialized, low level IO driver
 *@Return: None
 *@Precondition: None
 *@Postcondition: Button handle will be initialized and ready to use
 **************************************//**************************************/
void ButtonInit(ButtonIDNumber_t ButtonID, Button_Handle_t *Button, Button_IO_Drv_t IO){
	Button->IO_Driver   = IO;
	Button->IO_Driver.init();
	Button->ButtonIDNumber = ButtonID;
	Button->State = ButtonUnpressed;
}

/**************************************//**************************************
 *@Brief: Updates the state of a button
 *@Params: Button handle to read
 *@Return: ButtonChanged if the button changed states, otherwise ButtonUnchanged
 *@Precondition: ButtonHandle should be initialized/
 *@Postcondition: ButtonState in the ButtonHandle will be updated.
 **************************************//**************************************/
ButtonStatus_t ButtonRead(Button_Handle_t *Button){
    ButtonState_t Previous_State = Button->State;
    Button->State = Button->IO_Driver.read(Button->ButtonIDNumber);
    if(Previous_State != Button->State){
    	return ButtonChanged;
    } else {
    	return ButtonUnchanged;
    }
}



