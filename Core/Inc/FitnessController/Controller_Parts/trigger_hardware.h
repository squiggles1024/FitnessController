/*
 * trigger_hardware.h
 *
 *  Created on: Sep 2, 2022
 *      Author: evanl
 */

#ifndef INC_FITNESSCONTROLLER_CONTROLLER_PARTS_TRIGGER_HARDWARE_H_
#define INC_FITNESSCONTROLLER_CONTROLLER_PARTS_TRIGGER_HARDWARE_H_
/**************************************//**************************************//**************************************
 * Includes
 **************************************//**************************************//**************************************/
#include <stdint.h>

/**************************************//**************************************//**************************************
 * Driver Structs
 **************************************//**************************************//**************************************/
typedef struct{
    void (*init)(void);
    void (*deinit)(void);
    void (*read)(uint8_t*); //X Pos buffer, Y Pos buffer
    void (*write)(void);
    uint8_t (*ioctl)(uint8_t);
}Trigger_IO_Drv_t;

/**************************************//**************************************//**************************************
 * Exported Variables
 **************************************//**************************************//**************************************/
extern const Trigger_IO_Drv_t TriggerIO_Driver1;
extern const Trigger_IO_Drv_t TriggerIO_Driver2;



#endif /* INC_FITNESSCONTROLLER_CONTROLLER_PARTS_TRIGGER_HARDWARE_H_ */
