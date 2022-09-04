/*
 * HID.h
 *
 *  Created on: Jul 16, 2022
 *      Author: evanl
 */

#ifndef INC_FITNESSCONTROLLER_HIDSERVICE_HID_H_
#define INC_FITNESSCONTROLLER_HIDSERVICE_HID_H_
#include <stdint.h>

typedef struct{
	uint16_t bcdHID;
	uint8_t bCountryCode;
	uint8_t Flags;
} __attribute__((packed)) HIDInfoChar_t;

typedef struct{
	int16_t Sticks[4];
	uint8_t Triggers[2];
	uint16_t Buttons;
}__attribute__((packed)) HIDReportChar_t;

typedef uint8_t HIDControlPoint_t;

extern HIDControlPoint_t HIDControlPoint;
extern HIDReportChar_t HIDReport;
extern const HIDInfoChar_t HIDInfoValue;
extern const uint8_t HID_ReportMap[59];

#endif /* INC_FITNESSCONTROLLER_HIDSERVICE_HID_H_ */
