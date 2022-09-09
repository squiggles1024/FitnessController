/*
 * MAX30102.h
 *
 *  Created on: Sep 7, 2022
 *      Author: evanl
 */

#ifndef INC_FITNESSCONTROLLER_MAX30102_H_
#define INC_FITNESSCONTROLLER_MAX30102_H_
#include <stdint.h>
#include "MAX30102_Hardware.h"
/**************************************//**************************************//**************************************
 * Register Addresses
 **************************************//**************************************//**************************************/
//Status
#define MAX30102_REG_IRQSTATUS1 (0x00)
#define MAX30102_REG_IRQSTATUS2 (0x01)
#define MAX30102_REG_IRQENABLE1 (0x02)
#define MAX30102_REG_IRQENABLE2 (0x03)
#define MAX30102_REG_FIFOWRPTR  (0x04)
#define MAX30102_REG_FIFOOVFCTR (0x05)
#define MAX30102_REG_FIFORDPTR  (0x06)
#define MAX30102_REG_FIFODATA   (0x07)
//Config
#define MAX30102_REG_FIFOCONFIG   (0x08)
#define MAX30102_REG_MODECONFIG   (0x09)
#define MAX30102_REG_SPO2CONFIG   (0x0A)
#define MAX30102_REG_LEDPULSEAMP  (0x0CU)
#define MAX30102_REG_MULTILEDCTRL (0x11U)
//Die Temperature
#define MAX30102_REG_DIETEMPINTGR  (0x1FU)
#define MAX30102_REG_DIETEMPFRCT   (0x20U)
#define MAX30102_REG_DIETIMECONFIG (0x21U)
//Part ID
#define MAX30102_REG_RID (0xFEU)
#define MAX30102_REG_PID (0xFFU)

typedef enum{
	Max30102NoIRQ = 0,
    FifoAlmostFull = (1 << 7),
	HRDataReady = (1 << 6),
	AmbientLight = (1 << 5),
	DieTempReady = (1 << 9)
}MAX30102_IRQ_Mode_t;

typedef enum{
    NOAVERAGING = 0 << 5,
	TWOSAMPLESAVG = 1 << 5,
	FOURSAMPLESAVG = 2 << 5,
	EIGHTSAMPLESAVG = 3 << 5,
	SIXTEENSAMPLEAVG = 4 << 5,
	THIRTYTWOSAMPLEAVG = 5 << 5
}MAX30102_SamplingAvg_t;

typedef enum{
    FifoRollOverEnabbled = 1 << 4,
	FifoRollOverDisabled = 0
}MAX30102_FifoRollover_t;

typedef uint8_t MAX30102_FifoFullValue_t;

typedef enum{
	HeartRateMode = 2,
	SpO2Mode = 3,
	MultiLEDMode = 7
}MAX30102_ModeConfig_t;

typedef enum{
	FULLSCALE2048 = 0,
	FULLSCALE4096 = 1 << 5,
	FULLSCALE8192 = 2 << 5,
	FULLSCALE16384 = 3 << 5,
}MAX30102_ADC_FullScale_t;

typedef enum{
	SAMPLERATE50 = 0,
    SAMPLERATE100 = 1 << 2,
	SAMPLERATE200 = 2 << 2,
	SAMPLERATE400 = 3 << 2,
	SAMPLERATE800 = 4 << 2,
	SAMPLERATE1000 = 5 << 2,
	SAMPLERATE1600 = 6 << 2,
	SAMPLERATE3200 = 7 << 2,
}MAX30102_SPO2SampleRate_t;

typedef enum{
	LED_PULSEWIDTH69 = 0,
	LED_PULSEWIDTH118 = 1,
	LED_PULSEWIDTH215 = 2,
	LED_PULSEWIDTH1411 = 3
}MAX30102_LEDPulseWidth_t;


typedef struct{
	MAX30102_IRQ_Mode_t IRQMode;
	MAX30102_SamplingAvg_t SamplingAvg;
	MAX30102_FifoRollover_t RollOver;
	MAX30102_FifoFullValue_t FifoFull; //0x00-0x0F
	MAX30102_ModeConfig_t Mode;
	MAX30102_ADC_FullScale_t ADCFull;
	MAX30102_SPO2SampleRate_t SampleRate;
	MAX30102_LEDPulseWidth_t LED_PWM;
}MAX30102_Init_Struct_t;


typedef struct{
    uint32_t HeartRate;
    uint32_t SPO2;
    uint32_t DieTemp;
    MAX30102_IO_Drv_t IO;
}MAX30102_Handle_t;

/**************************************//**************************************//**************************************
 * Public Function Prototypes
 **************************************//**************************************//**************************************/
void MAX30102_Init(MAX30102_Init_Struct_t Settings, MAX30102_Handle_t *Dev, MAX30102_IO_Drv_t IO);
void MAX30102_DeInit(MAX30102_Handle_t *Dev);
void MAX30102_Reset(MAX30102_Handle_t *Dev);
MAX30102_Status_t MAX30102_ReadHeartRate(MAX30102_Handle_t *Dev);
void MAX30102_ReadReg(MAX30102_Handle_t *Dev, uint8_t reg, uint8_t *pdata, uint8_t length);
void MAX30102_WriteReg(MAX30102_Handle_t *Dev, uint8_t reg, uint8_t *pdata, uint8_t length);

#endif /* INC_FITNESSCONTROLLER_MAX30102_H_ */
