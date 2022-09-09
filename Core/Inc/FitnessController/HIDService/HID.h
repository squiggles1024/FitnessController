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
    uint8_t report_id;
    uint8_t report_type;
} __attribute__((packed)) HIDReportRefDesc_t;

typedef struct{
	uint16_t bcdHID;
	uint8_t bCountryCode;
	uint8_t Flags;
} __attribute__((packed)) HIDInfoChar_t;

typedef struct{
	//uint8_t report_id;
	uint8_t Dpad;
	uint16_t Buttons;
	uint8_t Triggers[2];
	int16_t Sticks[4];
}__attribute__((packed)) HIDReportChar_t;

typedef uint8_t HIDControlPoint_t;

extern HIDControlPoint_t HIDControlPoint;
extern HIDReportChar_t HIDReport;
extern const HIDInfoChar_t HIDInfoValue;
extern const uint8_t HID_ReportMap[92];
extern const HIDReportRefDesc_t ReportRefDesc;

#endif /* INC_FITNESSCONTROLLER_HIDSERVICE_HID_H_ */
