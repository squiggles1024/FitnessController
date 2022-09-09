/*
 * MAX30102_Hardware.h
 *
 *  Created on: Sep 7, 2022
 *      Author: evanl
 */

#ifndef INC_FITNESSCONTROLLER_MAX30102_HARDWARE_H_
#define INC_FITNESSCONTROLLER_MAX30102_HARDWARE_H_
#include <stdint.h>

typedef enum{
	MAX30102_Ok,
	MAX30102_Error
}MAX30102_Status_t;

typedef struct{
    void (*init)(void);
    MAX30102_Status_t (*read)(uint8_t, uint8_t*, uint8_t);
    MAX30102_Status_t (*write)(uint8_t, uint8_t*, uint8_t);
    void (*reset)(void);
    void (*ioctl)(uint8_t);
}MAX30102_IO_Drv_t;

extern MAX30102_IO_Drv_t MAX30102_Hardware_Drv;


#endif /* INC_FITNESSCONTROLLER_MAX30102_HARDWARE_H_ */
