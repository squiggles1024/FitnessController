/*
 * dpad_hardware.c
 *
 *  Created on: Sep 7, 2022
 *      Author: evanl
 */
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "dpad_hardware.h"
#include "stm32l4xx_hal.h"
#include "gpio.h"


/**************************************//**************************************//**************************************
 * Enums
 **************************************//**************************************//**************************************/
typedef enum{
	HatSwitchIO_Uninitialized = 0,
	HatSwitchIO_Initialized
}HatSwitch_IO_InitStatus_t;

/**************************************//**************************************//**************************************
 * Private Structs
 **************************************//**************************************//**************************************/
typedef struct{
	GPIO_TypeDef *GPIOPort;
	uint16_t GPIOPin;
}HatSwitchGPIOWrapper_t;


/**************************************//**************************************//**************************************
 * Private Variables
 **************************************//**************************************//**************************************/
static HatSwitch_IO_InitStatus_t initialize_status = HatSwitchIO_Uninitialized;

/**************************************//**************************************//**************************************
 * Private Function Definitions
 **************************************//**************************************//**************************************/
/**************************************//**************************************
 *@Brief: Initializes hardware devices needed to read a HatSwitch state
 *@Params: None
 *@Return: None
 *@Precondition: None
 *@Postcondition: GPIO Peripheral and clocks will be enabled and ready to use
 **************************************//**************************************/
static void HatSwitch_IO_init(void){

	if(initialize_status == HatSwitchIO_Uninitialized){
		Button_GPIO_Init();
	    initialize_status = HatSwitchIO_Initialized;
	}
}

static void HatSwitch_IO_deinit(void){

	if(initialize_status == HatSwitchIO_Initialized){
	    //de init GPIO. implement later.
	    initialize_status = HatSwitchIO_Uninitialized;
	}
}

/**************************************//**************************************
 *@Brief: Reads the state of a HatSwitch
 *@Params: Number of the HatSwitch to read
 *@Return: HatSwitchUnpressed if the HatSwitch is not pressed, HatSwitchPressed if it is pressed.
 *@Precondition: HatSwitch IO should be initialized
 *@Postcondition: None
 **************************************//**************************************/
static HatSwitchState_t HatSwitch_IO_Read(uint8_t HatSwitchNumber){
	GPIO_PinState UpState = HAL_GPIO_ReadPin(XINPUT_GAMEPAD_DPAD_UP_GPIO_Port, XINPUT_GAMEPAD_DPAD_UP_Pin);
	GPIO_PinState DownState = HAL_GPIO_ReadPin(XINPUT_GAMEPAD_DPAD_DOWN_GPIO_Port, XINPUT_GAMEPAD_DPAD_DOWN_Pin);
	GPIO_PinState LeftState = HAL_GPIO_ReadPin(XINPUT_GAMEPAD_DPAD_LEFT_GPIO_Port, XINPUT_GAMEPAD_DPAD_LEFT_Pin);
	GPIO_PinState RightState = HAL_GPIO_ReadPin(XINPUT_GAMEPAD_DPAD_RIGHT_GPIO_Port, XINPUT_GAMEPAD_DPAD_RIGHT_Pin);

    if(UpState && !DownState && !LeftState && !RightState){       //Up
		return HatUp;
	}else if(UpState && !DownState && !LeftState && RightState){  //UpRight
		return HatUpRight;
	}else if(!UpState && !DownState && !LeftState && RightState){ //Right
		return HatRight;
	}else if(!UpState && DownState && !LeftState && RightState){  //DownRight
		return HatDownRight;
	}else if(!UpState && DownState && !LeftState && !RightState){ //Down
		return HatDown;
	}else if(!UpState && DownState && LeftState && !RightState){  //DownLeft
		return HatDownLeft;
	}else if(!UpState && !DownState && LeftState && !RightState){ //Left
		return HatLeft;
	}else if(UpState && !DownState && LeftState && !RightState){ //UpLeft
		return HatUpLeft;
	}else{
		return HatNeutral;
	}

}

/**************************************//**************************************//**************************************
 * Public Variables
 **************************************//**************************************//**************************************/
//MCP23017_Handle_t Expander[NUMBER_OF_IO_EXPANDERS];

const HatSwitch_IO_Drv_t HatSwitchIO_Driver= {
		.init = HatSwitch_IO_init,
		.read = HatSwitch_IO_Read,
		.deinit = HatSwitch_IO_deinit,
		.write = '\0',
		.ioctl = '\0'
};




