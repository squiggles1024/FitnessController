/*
 * analog_stick_hardware.h
 *
 *  Created on: Sep 2, 2022
 *      Author: evanl
 */

#ifndef INC_FITNESSCONTROLLER_CONTROLLER_PARTS_ANALOG_STICK_HARDWARE_H_
#define INC_FITNESSCONTROLLER_CONTROLLER_PARTS_ANALOG_STICK_HARDWARE_H_
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include <stdint.h>

/**************************************//**************************************//**************************************
 * Driver Structs
 **************************************//**************************************//**************************************/
typedef struct{
    void (*init)(void); //4 byte buffer to store data
    void (*deinit)(void);
    void (*read)(int16_t*, int16_t*); //Deadzone, X Pos buffer, Y Pos buffer
    void (*write)(void);
    uint8_t (*ioctl)(uint8_t);
}AnalogStick_IO_Drv_t;

/**************************************//**************************************//**************************************
 * Exported Variables
 **************************************//**************************************//**************************************/
extern const AnalogStick_IO_Drv_t AnalogStickIO_Driver1;
extern const AnalogStick_IO_Drv_t AnalogStickIO_Driver2;


#endif /* INC_FITNESSCONTROLLER_CONTROLLER_PARTS_ANALOG_STICK_HARDWARE_H_ */
