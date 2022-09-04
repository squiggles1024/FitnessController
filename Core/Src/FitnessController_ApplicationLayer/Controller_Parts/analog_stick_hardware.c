/*
 * analog_stick_hardware.c
 *
 *  Created on: Sep 3, 2022
 *      Author: evanl
 */
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include <stdint.h>
#include "analog_stick_hardware.h"
#include "gpio.h"
#include "adc.h"
#include "dma.h"

/**************************************//**************************************//**************************************
 * Private Variables
 **************************************//**************************************//**************************************/
#define ADC_LX_INDEX  (0U)
#define ADC_LY_INDEX  (1U)
#define ADC_RX_INDEX  (2U)
#define ADC_RY_INDEX  (3U)

/**************************************//**************************************//**************************************
 * Private Function Defintions
 **************************************//**************************************//**************************************/
/**************************************//**************************************
 *@Brief: Calls low level IO necessary to read AnalogStick values
 *@Params: None
 *@Return: None
 *@Precondition: None
 *@Postcondition: Low level hardware will be initialized. (DMA, ADC, GPIO)
 **************************************//**************************************/
static void AnalogStickIOInit(){
	if(ADC_Init_Status == ADC_UNINITIALIZED){
	    ADC_GPIO_Init();
	    ADC_DMA_Init();
	    ADC1_Init();
	    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_buffer, sizeof(adc_buffer));
	ADC_Init_Status = ADC_INITIALIZED;
	}
}

/**************************************//**************************************
 *@Brief: Stops AnalogStick DMA transfers, disables its IRQ, and clears any pending IRQ.
 *@Params: None
 *@Return: None
 *@Precondition: None
 *@Postcondition: DMA transfers from AnalogStick will be stopped.
 **************************************//**************************************/
static void AnalogStickIODeInit(void){
   HAL_ADC_Stop_DMA(&hadc1);
   HAL_NVIC_DisableIRQ(DMA1_Channel1_IRQn);
   HAL_NVIC_ClearPendingIRQ(DMA1_Channel1_IRQn);
}

/**************************************//**************************************
 *@Brief: Reads the AnalogStick ADC buffer and scales the output to a 16 bit integer
 *@Params: AnalogStick Deadzone, X Position buffer, Y Position buffer
 *@Return: Position of the AnalogStick
 *@Precondition: AnalogStick IO should be initialized
 *@Postcondition: X_Pos and Y_Pos will contain raw AnalogStick value.
 **************************************//**************************************/
static void AnalogStickIORead1(int16_t *X_Pos, int16_t *Y_Pos){
	int16_t Convert = (adc_buffer[ADC_LX_INDEX] << 4) - 32767;
	if(Convert < 3276 && Convert > -3277){ //10% of Max
		Convert = 0;
	}
	*X_Pos = Convert;

    Convert = (adc_buffer[ADC_LY_INDEX] << 4) - 32767;
	if(Convert < 3276 && Convert > -3277){ //10% of Max
		Convert = 0;
	}
	*Y_Pos = Convert;
}

static void AnalogStickIORead2(int16_t *X_Pos, int16_t *Y_Pos){
	int16_t Convert = (adc_buffer[ADC_RX_INDEX] << 4) - 32767;
	if(Convert < 3276 && Convert > -3277){ //10% of Max
		Convert = 0;
	}
	*X_Pos = Convert;

    Convert = (adc_buffer[ADC_RY_INDEX] << 4) - 32767;
	if(Convert < 3276 && Convert > -3277){ //10% of Max
		Convert = 0;
	}
	*Y_Pos = Convert;
}

/**************************************//**************************************//**************************************
 * Exported Variable Definitions
 **************************************//**************************************//**************************************/
const AnalogStick_IO_Drv_t AnalogStickIO_Driver1 = {
	.init = AnalogStickIOInit,
	.deinit = AnalogStickIODeInit,
	.read = AnalogStickIORead1,
	.write = '\0',
	.ioctl = '\0'
};

const AnalogStick_IO_Drv_t AnalogStickIO_Driver2 = {
	.init = AnalogStickIOInit,
	.deinit = AnalogStickIODeInit,
	.read = AnalogStickIORead2,
	.write = '\0',
	.ioctl = '\0'
};


