/*
 * HID.c
 *
 *  Created on: Jul 16, 2022
 *      Author: evanl
 */

#include "HID.h"

#define USB_HID_CLASS_SPEC (0x0111)
#define USB_bCOUNTRYCODE (33) //USA / English
#define USB_FLAG_NONE (0x0)
#define USB_FLAG_REMOTEWAKE (0x1)
#define USB_FLAG_NORMALLYCONNECTABLE (0x2)
#define USB_INPUT_REPORT (0x01)

HIDControlPoint_t HIDControlPoint = 0;

HIDReportChar_t HIDReport = {
		//.report_id = 1,
		.Sticks = { 0, 0 , 0, 0},
		.Triggers = {0, 0},
		.Buttons = 0
};

const HIDInfoChar_t HIDInfoValue = {
		.bcdHID = USB_HID_CLASS_SPEC,
		.bCountryCode = USB_bCOUNTRYCODE,
		.Flags = USB_FLAG_REMOTEWAKE
};

const HIDReportRefDesc_t ReportRefDesc = {
		.report_id = 1,
		.report_type = USB_INPUT_REPORT
};

const uint8_t HID_ReportMap[84] = {
	    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
	    0x09, 0x05,                    // USAGE (Game Pad)
	    0xa1, 0x01,                    // COLLECTION (Application)
	    0x85, 0x01,                    //   REPORT_ID (1)
	    0x09, 0x39,                    //   USAGE (Hat switch)
	    0x15, 0x01,                    //   LOGICAL_MINIMUM (1)
	    0x25, 0x08,                    //   LOGICAL_MAXIMUM (8)
	    0x75, 0x04,                    //   REPORT_SIZE (4)
	    0x95, 0x01,                    //   REPORT_COUNT (1)
	    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
	    0x05, 0x09,                    //   USAGE_PAGE (Button)
	    0x19, 0x01,                    //   USAGE_MINIMUM (Button 1)
	    0x29, 0x0c,                    //   USAGE_MAXIMUM (Button 12)
	    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
	    0x75, 0x01,                    //   REPORT_SIZE (1)
	    0x95, 0x0c,                    //   REPORT_COUNT (12)
	    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
	    0x05, 0x01,                    //   USAGE_PAGE (Generic Desktop)
	    0x09, 0x32,                    //   USAGE (Z)
	    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
	    0x75, 0x08,                    //   REPORT_SIZE (8)
	    0x95, 0x01,                    //   REPORT_COUNT (1)
	    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
	    0x09, 0x35,                    //   USAGE (Rz)
	    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
	    0xa1, 0x00,                    //   COLLECTION (Physical)
	    0x09, 0x30,                    //     USAGE (X)
	    0x09, 0x31,                    //     USAGE (Y)
	    0x16, 0x00, 0x80,              //     LOGICAL_MINIMUM (-32768)
	    0x26, 0xff, 0x7f,              //     LOGICAL_MAXIMUM (32767)
	    0x75, 0x10,                    //     REPORT_SIZE (16)
	    0x95, 0x02,                    //     REPORT_COUNT (2)
	    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
	    0xc0,                          //   END_COLLECTION
	    0xa1, 0x00,                    //   COLLECTION (Physical)
	    0x09, 0x33,                    //     USAGE (Rx)
	    0x09, 0x34,                    //     USAGE (Ry)
	    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
	    0xc0,                          //   END_COLLECTION
	    0xc0                           // END_COLLECTION
	};
