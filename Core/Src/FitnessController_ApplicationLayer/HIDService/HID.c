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

HIDControlPoint_t HIDControlPoint = 0;

HIDReportChar_t HIDReport = {
		.Sticks = { 0, 0 },
		.Triggers = {0, 0},
		.Buttons = 0
};

const HIDInfoChar_t HIDInfoValue = {
		.bcdHID = USB_HID_CLASS_SPEC,
		.bCountryCode = USB_bCOUNTRYCODE,
		.Flags = USB_FLAG_REMOTEWAKE
};

const uint8_t HID_ReportMap[59] = {
	    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
	    0x09, 0x05,                    // USAGE (Game Pad)
	    0xa1, 0x01,                    // COLLECTION (Application)
	    0xa1, 0x00,                    //   COLLECTION (Physical)
	    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
	    0x09, 0x30,                    //     USAGE (X)
	    0x09, 0x31,                    //     USAGE (Y)
	    0x09, 0x32,                    //     USAGE (Z)
	    0x09, 0x33,                    //     USAGE (Rx)
	    0x16, 0x5a, 0x80,              //     LOGICAL_MINIMUM (-32678)
	    0x26, 0xff, 0x7f,              //     LOGICAL_MAXIMUM (32767)
	    0x75, 0x10,                    //     REPORT_SIZE (16)
	    0x95, 0x04,                    //     REPORT_COUNT (4)
	    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
	    0x09, 0x34,                    //     USAGE (Ry)
	    0x09, 0x35,                    //     USAGE (Rz)
	    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
	    0x26, 0xff, 0x00,              //     LOGICAL_MAXIMUM (255)
	    0x75, 0x08,                    //     REPORT_SIZE (8)
	    0x95, 0x02,                    //     REPORT_COUNT (2)
	    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
	    0x05, 0x09,                    //     USAGE_PAGE (Button)
	    0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
	    0x29, 0x10,                    //     USAGE_MAXIMUM (Button 16)
	    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
	    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
	    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
	    0xc0,                          //   END_COLLECTION
	    0xc0                           // END_COLLECTION
	};
