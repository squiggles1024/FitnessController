/*
 * HIDService.h
 *
 *  Created on: Jul 13, 2022
 *      Author: evanl
 */

#ifndef INC_FITNESSCONTROLLER_HIDSERVICE_HIDSERVICE_H_
#define INC_FITNESSCONTROLLER_HIDSERVICE_HIDSERVICE_H_
#include <stdint.h>

typedef enum{
     HID_InfoCharErr,
     HID_ReportMapCharErr,
	 HID_ControlPtCharErr,
	 HID_ReportCharErr,
	 HID_AddServiceErr,
	 HID_OK
}HIDServiceStatus_t;

HIDServiceStatus_t AddHIDService(void);

uint16_t GetHIDServiceHandle(void);


#endif /* INC_FITNESSCONTROLLER_HIDSERVICE_HIDSERVICE_H_ */
