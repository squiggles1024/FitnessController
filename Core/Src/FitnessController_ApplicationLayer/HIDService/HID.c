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
		.Sticks = { 2047, 2047 },
		.Triggers = {0, 0},
		.Buttons = 0
};

const HIDInfoChar_t HIDInfoValue = {
		.bcdHID = USB_HID_CLASS_SPEC,
		.bCountryCode = USB_bCOUNTRYCODE,
		.Flags = USB_FLAG_REMOTEWAKE
};

const uint8_t HID_ReportMap[178] = {
	    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
	    0x09, 0x05,                    // USAGE (Game Pad)
	    0xa1, 0x01,                    // COLLECTION (Application)
	    0xa1, 0x00,                    //   COLLECTION (Physical)
	    0x09, 0x30,                    //     USAGE (X)
	    0x09, 0x31,                    //     USAGE (Y)
	    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
	    0x26, 0xff, 0x0f,              //     LOGICAL_MAXIMUM (4095)
	    0x95, 0x02,                    //     REPORT_COUNT (2)
	    0x75, 0x0c,                    //     REPORT_SIZE (12)
	    0x81, 0x02,                    //     INPUT (Data,Var,Abs)           STICK 1 (12 Bits)
	    0xc0,                          //   END_COLLECTION
	    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	    0x25, 0x00,                    //   LOGICAL_MAXIMUM (0)
	    0x95, 0x01,                    //   REPORT_COUNT (1)
	    0x75, 0x04,                    //   REPORT_SIZE (4)
	    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)             4 PADDING BITS
	    0xa1, 0x00,                    //   COLLECTION (Physical)
	    0x09, 0x33,                    //     USAGE (Rx)
	    0x09, 0x34,                    //     USAGE (Ry)
	    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
	    0x26, 0xff, 0x0f,              //     LOGICAL_MAXIMUM (4095)
	    0x95, 0x02,                    //     REPORT_COUNT (2)
	    0x75, 0x0c,                    //     REPORT_SIZE (12)
	    0x81, 0x02,                    //     INPUT (Data,Var,Abs)           STICK 2 (12 Bits)
	    0xc0,                          //   END_COLLECTION
	    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	    0x25, 0x00,                    //   LOGICAL_MAXIMUM (0)
	    0x75, 0x04,                    //   REPORT_SIZE (4)
	    0x95, 0x01,                    //   REPORT_COUNT (1)
	    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)            4 PADDING BITS
	    0x05, 0x01,                    //   USAGE_PAGE (Generic Desktop)
	    0x09, 0x32,                    //   USAGE (Z)
	    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	    0x26, 0xff, 0x03,              //   LOGICAL_MAXIMUM (1023)
	    0x95, 0x01,                    //   REPORT_COUNT (1)
	    0x75, 0x0a,                    //   REPORT_SIZE (10)
	    0x81, 0x02,                    //   INPUT (Data,Var,Abs)           TRIGGER 1 (10 Bits)
	    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	    0x25, 0x00,                    //   LOGICAL_MAXIMUM (0)
	    0x75, 0x06,                    //   REPORT_SIZE (6)
	    0x95, 0x01,                    //   REPORT_COUNT (1)
	    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)           6 PADDING BITS
	    0x05, 0x01,                    //   USAGE_PAGE (Generic Desktop)
	    0x09, 0x35,                    //   USAGE (Rz)
	    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	    0x26, 0xff, 0x03,              //   LOGICAL_MAXIMUM (1023)
	    0x95, 0x01,                    //   REPORT_COUNT (1)
	    0x75, 0x0a,                    //   REPORT_SIZE (10)
	    0x81, 0x02,                    //   INPUT (Data,Var,Abs)           TRIGGER 2 (10 Bits)
	    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	    0x25, 0x00,                    //   LOGICAL_MAXIMUM (0)
	    0x75, 0x06,                    //   REPORT_SIZE (6)
	    0x95, 0x01,                    //   REPORT_COUNT (1)
	    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)           6 PADDING BITS
	    0x05, 0x01,                    //   USAGE_PAGE (Generic Desktop)
	    0x09, 0x39,                    //   USAGE (Hat switch)
	    0x15, 0x01,                    //   LOGICAL_MINIMUM (1)
	    0x25, 0x08,                    //   LOGICAL_MAXIMUM (8)
	    0x35, 0x00,                    //   PHYSICAL_MINIMUM (0)
	    0x46, 0x3b, 0x01,              //   PHYSICAL_MAXIMUM (315)
	    0x65, 0x14,                    //   UNIT (Eng Rot:Angular Pos)
	    0x75, 0x04,                    //   REPORT_SIZE (4)
	    0x95, 0x01,                    //   REPORT_COUNT (1)
	    0x81, 0x02,                    //   INPUT (Data,Var,Abs)          D-PAD 4 BITS
	    0x65, 0x00,                    //   UNIT (None)
	    0x75, 0x04,                    //   REPORT_SIZE (4)
	    0x95, 0x01,                    //   REPORT_COUNT (1)
	    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	    0x25, 0x00,                    //   LOGICAL_MAXIMUM (0)
	    0x35, 0x00,                    //   PHYSICAL_MINIMUM (0)
	    0x45, 0x00,                    //   PHYSICAL_MAXIMUM (0)
	    0x65, 0x00,                    //   UNIT (None)
	    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)         4 PADDING BITS
	    0x05, 0x09,                    //   USAGE_PAGE (Button)
	    0x19, 0x01,                    //   USAGE_MINIMUM (Button 1)
	    0x29, 0x0f,                    //   USAGE_MAXIMUM (Button 15)
	    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
	    0x75, 0x01,                    //   REPORT_SIZE (1)
	    0x95, 0x0f,                    //   REPORT_COUNT (15)
	    0x81, 0x02,                    //   INPUT (Data,Var,Abs)        15 BUTTON BITS
	    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	    0x25, 0x00,                    //   LOGICAL_MAXIMUM (0)
	    0x75, 0x01,                    //   REPORT_SIZE (1)             1 PADDING BIT
	    0x95, 0x01,                    //   REPORT_COUNT (1)
	    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
	    0xc0                           // END_COLLECTION
};
