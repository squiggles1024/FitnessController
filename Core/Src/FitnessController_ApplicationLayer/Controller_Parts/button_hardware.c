/*
 * button_hardware.c
 *
 *  Created on: Sep 2, 2022
 *      Author: evanl
 */
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "button_hardware.h"
#include "stm32l4xx_hal.h"
#include "gpio.h"


/**************************************//**************************************//**************************************
 * Enums
 **************************************//**************************************//**************************************/
typedef enum{
	ButtonIO_Uninitialized = 0,
	ButtonIO_Initialized
}Button_IO_InitStatus_t;

/**************************************//**************************************//**************************************
 * Private Structs
 **************************************//**************************************//**************************************/
typedef struct{
	GPIO_TypeDef *GPIOPort;
	uint16_t GPIOPin;
}ButtonGPIOWrapper_t;


/**************************************//**************************************//**************************************
 * Private Variables
 **************************************//**************************************//**************************************/
static Button_IO_InitStatus_t initialize_status = ButtonIO_Uninitialized;

static const ButtonGPIOWrapper_t ButtonGPIOLUT[NUMBER_OF_BUTTONS] = {
		{XINPUT_GAMEPAD_A_GPIO_Port, XINPUT_GAMEPAD_A_Pin},                           //1
		{XINPUT_GAMEPAD_B_GPIO_Port, XINPUT_GAMEPAD_B_Pin},                           //2
		{XINPUT_GAMEPAD_X_GPIO_Port, XINPUT_GAMEPAD_X_Pin},                           //3
		{XINPUT_GAMEPAD_Y_GPIO_Port, XINPUT_GAMEPAD_Y_Pin},                           //4
		{XINPUT_GAMEPAD_START_GPIO_Port, XINPUT_GAMEPAD_START_Pin},                   //5
		{XINPUT_GAMEPAD_BACK_GPIO_Port, XINPUT_GAMEPAD_BACK_Pin},                     //6
		{XINPUT_GAMEPAD_LEFT_THUMB_GPIO_Port, XINPUT_GAMEPAD_LEFT_THUMB_Pin},         //7
		{XINPUT_GAMEPAD_RIGHT_THUMB_GPIO_Port, XINPUT_GAMEPAD_RIGHT_THUMB_Pin},       //8
		{XINPUT_GAMEPAD_LEFT_SHOULDER_GPIO_Port, XINPUT_GAMEPAD_LEFT_SHOULDER_Pin},   //9
		{XINPUT_GAMEPAD_RIGHT_SHOULDER_GPIO_Port, XINPUT_GAMEPAD_RIGHT_SHOULDER_Pin}, //10

};
/**************************************//**************************************//**************************************
 * Private Function Definitions
 **************************************//**************************************//**************************************/
/**************************************//**************************************
 *@Brief: Initializes hardware devices needed to read a button state
 *@Params: None
 *@Return: None
 *@Precondition: None
 *@Postcondition: GPIO Peripheral and clocks will be enabled and ready to use
 **************************************//**************************************/
static void Button_IO_init(void){

	if(initialize_status == ButtonIO_Uninitialized){
		Button_GPIO_Init();
	    initialize_status = ButtonIO_Initialized;
	}
}

static void Button_IO_deinit(void){

	if(initialize_status == ButtonIO_Initialized){
	    //de init GPIO. implement later.
	    initialize_status = ButtonIO_Uninitialized;
	}
}

/**************************************//**************************************
 *@Brief: Reads the state of a button
 *@Params: Number of the button to read
 *@Return: ButtonUnpressed if the button is not pressed, ButtonPressed if it is pressed.
 *@Precondition: Button IO should be initialized
 *@Postcondition: None
 **************************************//**************************************/
static ButtonState_t Button_IO_ReadPosLogic(uint8_t ButtonNumber){
	GPIO_PinState State = HAL_GPIO_ReadPin(ButtonGPIOLUT[ButtonNumber].GPIOPort, ButtonGPIOLUT[ButtonNumber].GPIOPin);
	if(State == GPIO_PIN_SET){
		return ButtonPressed;
	} else {
		return ButtonUnpressed;
	}
}

static ButtonState_t Button_IO_ReadNegLogic(uint8_t ButtonNumber){
	GPIO_PinState State = HAL_GPIO_ReadPin(ButtonGPIOLUT[ButtonNumber].GPIOPort, ButtonGPIOLUT[ButtonNumber].GPIOPin);
	if(State == GPIO_PIN_SET){
		return ButtonUnpressed;
	} else {
		return ButtonPressed;
	}
}

/**************************************//**************************************//**************************************
 * Public Variables
 **************************************//**************************************//**************************************/
//MCP23017_Handle_t Expander[NUMBER_OF_IO_EXPANDERS];

const Button_IO_Drv_t ButtonIO_DriverPosLogic = {
		.init = Button_IO_init,
		.read = Button_IO_ReadPosLogic,
		.deinit = Button_IO_deinit,
		.write = '\0',
		.ioctl = '\0'
};

const Button_IO_Drv_t ButtonIO_DriverNegLogic = {
		.init = Button_IO_init,
		.read = Button_IO_ReadNegLogic,
		.deinit = Button_IO_deinit,
		.write = '\0',
		.ioctl = '\0'
};

