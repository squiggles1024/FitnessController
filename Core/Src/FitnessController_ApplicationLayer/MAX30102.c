/*
 * MAX30102.c
 *
 *  Created on: Sep 7, 2022
 *      Author: evanl
 */
#include "MAX30102.h"

void MAX30102_Init(MAX30102_Init_Struct_t Settings, MAX30102_Handle_t *Dev, MAX30102_IO_Drv_t IO){
	Dev->IO = IO;
	uint32_t dummy_reg = 0;
	dummy_reg = Settings.IRQMode;
	Dev->IO.init();
	Dev->IO.write(MAX30102_REG_IRQENABLE1, (uint8_t*)&dummy_reg, 1);

	dummy_reg = Settings.SamplingAvg | Settings.FifoFull | Settings.RollOver;
	Dev->IO.write(MAX30102_REG_FIFOCONFIG, (uint8_t*)&dummy_reg,1);

	dummy_reg = Settings.Mode;
	Dev->IO.write(MAX30102_REG_MODECONFIG, (uint8_t*)&dummy_reg,1);

	dummy_reg = Settings.ADCFull | Settings.SampleRate | Settings.LED_PWM;
	Dev->IO.write(MAX30102_REG_SPO2CONFIG,(uint8_t*)&dummy_reg,1);
}

void MAX30102_DeInit(MAX30102_Handle_t *Dev){
	//to be implemented
}

void MAX30102_Reset(MAX30102_Handle_t *Dev){
 uint8_t reset_signal = 1 << 6;
 Dev->IO.write(MAX30102_REG_MODECONFIG,&reset_signal,1);
}

MAX30102_Status_t MAX30102_ReadHeartRate(MAX30102_Handle_t *Dev){
	uint8_t dummy = 0;
	MAX30102_Status_t ret = 0;
	ret |= Dev->IO.read(MAX30102_REG_FIFOWRPTR,&dummy,1); //read WR pointer
	if(dummy > 0){
		dummy = dummy - 1;
	}
	ret |= Dev->IO.write(MAX30102_REG_FIFORDPTR,&dummy,1); //write to RD ptr
	ret |= Dev->IO.read(MAX30102_REG_FIFODATA, (uint8_t*)&Dev->HeartRate,3);
	return ret;
}

void MAX30102_ReadReg(MAX30102_Handle_t *Dev, uint8_t reg, uint8_t *pdata, uint8_t length){
	Dev->IO.read(reg,pdata,length);
}

void MAX30102_WriteReg(MAX30102_Handle_t *Dev, uint8_t reg, uint8_t *pdata, uint8_t length){
	Dev->IO.write(reg,pdata,length);
}
