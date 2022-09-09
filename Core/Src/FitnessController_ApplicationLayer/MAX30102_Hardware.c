/*
 * MAX30102_Hardware.c
 *
 *  Created on: Sep 7, 2022
 *      Author: evanl
 */
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include "MAX30102_Hardware.h"
#include <stdio.h>
#include "stm32l4xx_hal.h"
#include "gpio.h"
#include "i2c.h"

/**************************************//**************************************//**************************************
 * Defines / Constants
 **************************************//**************************************//**************************************/
static const uint8_t MAX30102_DEVICE_ADDRESS = 0xAEU;
static const uint16_t MAX30102_TIMEOUT_MS = 50;

/**************************************//**************************************//**************************************
 * Private Function Prototypes
 **************************************//**************************************//**************************************/
static void MAX30102_Init();
static void MAX30102_DeInit();
static MAX30102_Status_t MAX30102_WriteReg(uint8_t reg, uint8_t *pdata, uint8_t length);
static MAX30102_Status_t MAX30102_ReadReg(uint8_t reg, uint8_t *pdata, uint8_t length);

/**************************************//**************************************//**************************************
 * Private Function Definitions
 **************************************//**************************************//**************************************/

/*Initializes low level IO*/
static void MAX30102_Init(){
	HAL_Delay(20); //Device takes 20 ms to boot.
//	MX_GPIO_Init();
	MAX30102_GPIO_Init();
//	MX_I2C1_Init();
}

/*DeInitializes low level IO.*/
static void MAX30102_DeInit(){
	//Do Not De-Init I2C Peripheral as other devices may be using it.
	//To be implemented
}

/*Sends data to register over I2C2 Bus*/
static MAX30102_Status_t MAX30102_WriteReg(uint8_t reg, uint8_t *pdata, uint8_t length){
	if(HAL_I2C_Mem_Write(&hi2c1, MAX30102_DEVICE_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, pdata , length, MAX30102_TIMEOUT_MS) != HAL_OK){
		printf("Write to MAX30102 Reg address %x failed.",reg);
		return MAX30102_Error;
	}
	return MAX30102_Ok;
}

/*Reads data from register over I2C2 Bus*/
static MAX30102_Status_t MAX30102_ReadReg(uint8_t reg, uint8_t *pdata, uint8_t length){
	if(HAL_I2C_Mem_Read(&hi2c1, MAX30102_DEVICE_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, pdata , length, MAX30102_TIMEOUT_MS) != HAL_OK){
		printf("Read from MAX30102 Reg address %x failed.",reg);
		return MAX30102_Error;
	}
	return MAX30102_Ok;
}


/**************************************//**************************************//**************************************
 * Public Variable Defitinion
 **************************************//**************************************//**************************************/
MAX30102_IO_Drv_t MAX30102_Hardware_Drv = {
		.init = MAX30102_Init,
		.reset = MAX30102_DeInit,
		.write = MAX30102_WriteReg,
		.read = MAX30102_ReadReg,
		.ioctl = '\0'
};


