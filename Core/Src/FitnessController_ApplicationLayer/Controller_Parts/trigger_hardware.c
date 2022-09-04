/*
 * trigger_hardware.c
 *
 *  Created on: Sep 3, 2022
 *      Author: evanl
 */
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include <stdint.h>
#include "trigger_hardware.h"
#include "gpio.h"
#include "adc.h"
#include "dma.h"

/**************************************//**************************************//**************************************
 * Private Variables
 **************************************//**************************************//**************************************/
#define ADC_LT_INDEX  (4U)
#define ADC_RT_INDEX  (5U)
#define TRIGGER_10PERCENT_PULLED (2048U + 409)
#define TRIGGER_ADC_OFFSET (2048U)

/**************************************//**************************************//**************************************
 * Private Function Defintions
 **************************************//**************************************//**************************************/
/**************************************//**************************************
 *@Brief: Calls low level IO necessary to read Trigger values
 *@Params: None
 *@Return: None
 *@Precondition: None
 *@Postcondition: Low level hardware will be initialized. (DMA, ADC, GPIO)
 **************************************//**************************************/
static void TriggerIOInit(){
	if(ADC_Init_Status == ADC_UNINITIALIZED){
	    ADC_GPIO_Init();
	    ADC_DMA_Init();
	    ADC1_Init();
	    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_buffer, sizeof(adc_buffer));
	ADC_Init_Status = ADC_INITIALIZED;
	}
}

/**************************************//**************************************
 *@Brief: Stops Trigger DMA transfers, disables its IRQ, and clears any pending IRQ.
 *@Params: None
 *@Return: None
 *@Precondition: None
 *@Postcondition: DMA transfers from Trigger will be stopped.
 **************************************//**************************************/
static void TriggerIODeInit(void){
   HAL_ADC_Stop_DMA(&hadc1);
   HAL_NVIC_DisableIRQ(DMA1_Channel1_IRQn);
   HAL_NVIC_ClearPendingIRQ(DMA1_Channel1_IRQn);
}

/**************************************//**************************************
 *@Brief: Reads the Trigger ADC buffer and scales the output to a 16 bit integer
 *@Params: Trigger Deadzone, X Position buffer, Y Position buffer
 *@Return: Position of the Trigger
 *@Precondition: Trigger IO should be initialized
 *@Postcondition: X_Pos and Y_Pos will contain raw Trigger value.
 **************************************//**************************************/
static void TriggerIORead1(uint8_t *Pos){
	uint8_t Convert;
    uint16_t Value = adc_buffer[ADC_LT_INDEX];
	if(Value < TRIGGER_10PERCENT_PULLED){
		Convert = 0;
	} else {
		Convert = (Value - TRIGGER_ADC_OFFSET) >> 3; //convert to 8 bits
	}
	if(Convert <= 25){ //10% of Max
		Convert = 0;
	}
	*Pos = Convert;
}

static void TriggerIORead2(uint8_t *Pos){
	uint8_t Convert;
	uint16_t Value = adc_buffer[ADC_RT_INDEX];
	if(Value < TRIGGER_10PERCENT_PULLED){
		Convert = 0;
	} else {
		Convert = (Value - TRIGGER_ADC_OFFSET) >> 3; //convert to 8 bits
	}
	if(Convert <= 25){ //10% of Max
		Convert = 0;
	}
	*Pos = Convert;
}

/**************************************//**************************************//**************************************
 * Exported Variable Definitions
 **************************************//**************************************//**************************************/
const Trigger_IO_Drv_t TriggerIO_Driver1 = {
	.init = TriggerIOInit,
	.deinit = TriggerIODeInit,
	.read = TriggerIORead1,
	.write = '\0',
	.ioctl = '\0'
};

const Trigger_IO_Drv_t TriggerIO_Driver2 = {
	.init = TriggerIOInit,
	.deinit = TriggerIODeInit,
	.read = TriggerIORead2,
	.write = '\0',
	.ioctl = '\0'
};



