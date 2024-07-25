// EzUsbFirmware.cpp - EZUSB device firmware
//====================================================================================================
//
// Compuware Corporation
// NuMega Lab
// 9 Townsend West
// Nashua, NH 03060 USA
//
// Copyright (c) 1999 Compuware Corporation. All Rights Reserved.
// Unpublished - rights reserved under the Copyright laws of the
// United States.
//
//====================================================================================================
// Portions of this file used with permission of Cypress/Anchor.
// Copyright (c) 1997 Anchor Chips, Inc.  May not be reproduced without permission.  

extern "C" {
#pragma warning (disable:4201)
#pragma warning (disable:4514)
#pragma warning (disable:4200)
#include <wdm.h>
}

#include "EzUsbFirmware.h"

//====================================================================================================
//
//	This data structure is firmware for the development kit.  It implements a vendor specific command
//	EZUSB_LOAD_EXTERNAL which enables downloading firmware to external RAM of the EZUSB chip.
//
INTEL_HEX_RECORD loader[] = {
	16,	0x146c, 0,  {0xc2,0x00,0x90,0x7f,0xa5,0xe0,0x54,0x18,0xff,0x13,0x13,0x13,0x54,0x1f,0x44,0x50},
	16, 0x147c, 0,  {0xf5,0x1c,0x13,0x92,0x01,0xd2,0xe8,0x90,0x7f,0xab,0x74,0xff,0xf0,0x90,0x7f,0xa9},
	16, 0x148c, 0,  {0xf0,0x90,0x7f,0xaa,0xf0,0x53,0x91,0xef,0x90,0x7f,0x95,0xe0,0x44,0xc0,0xf0,0x90},
	16, 0x149c, 0,  {0x7f,0xaf,0xe0,0x44,0x01,0xf0,0x90,0x7f,0xae,0xe0,0x44,0x05,0xf0,0xd2,0xaf,0x12},
	13, 0x14ac, 0,  {0x17,0x5f,0x30,0x00,0xfd,0x12,0x11,0x00,0xc2,0x00,0x80,0xf6,0x22},
	16, 0x1100, 0,  {0x90,0x7f,0xe9,0xe0,0x24,0x5d,0x60,0x0d,0x14,0x70,0x03,0x02,0x12,0x44,0x24,0x02},
	16, 0x1110, 0,  {0x60,0x03,0x02,0x12,0x4a,0x90,0x7f,0xea,0xe0,0x75,0x08,0x00,0xf5,0x09,0xa3,0xe0},
	16, 0x1120, 0,  {0xfe,0xe4,0x25,0x09,0xf5,0x09,0xee,0x35,0x08,0xf5,0x08,0x90,0x7f,0xee,0xe0,0x75},
	16, 0x1130, 0,  {0x0a,0x00,0xf5,0x0b,0xa3,0xe0,0xfe,0xe4,0x25,0x0b,0xf5,0x0b,0xee,0x35,0x0a,0xf5},
	16, 0x1140, 0,  {0x0a,0x90,0x7f,0xe8,0xe0,0x64,0xc0,0x60,0x03,0x02,0x11,0xd4,0xe5,0x0b,0x45,0x0a},
	16, 0x1150, 0,  {0x70,0x03,0x02,0x12,0x4a,0xc3,0xe5,0x0b,0x94,0x40,0xe5,0x0a,0x94,0x00,0x50,0x08},
	16, 0x1160, 0,  {0x85,0x0a,0x0c,0x85,0x0b,0x0d,0x80,0x06,0x75,0x0c,0x00,0x75,0x0d,0x40,0x90,0x7f},
	16, 0x1170, 0,  {0xe9,0xe0,0xb4,0xa3,0x25,0xae,0x0c,0xaf,0x0d,0xaa,0x08,0xa9,0x09,0x7b,0x01,0xc0},
	16, 0x1180, 0,  {0x03,0xc0,0x02,0xc0,0x01,0x7a,0x7f,0x79,0x00,0x78,0x00,0x7c,0x7f,0xad,0x03,0xd0},
	16, 0x1190, 0,  {0x01,0xd0,0x02,0xd0,0x03,0x12,0x13,0x56,0x80,0x0f,0xaf,0x09,0xae,0x08,0xad,0x0d},
	16, 0x11a0, 0,  {0x7a,0x7f,0x79,0x00,0x7b,0x00,0x12,0x15,0xa4,0x90,0x7f,0xb5,0xe5,0x0d,0xf0,0xe5},
	16, 0x11b0, 0,  {0x0d,0x25,0x09,0xf5,0x09,0xe5,0x0c,0x35,0x08,0xf5,0x08,0xc3,0xe5,0x0b,0x95,0x0d},
	16, 0x11c0, 0,  {0xf5,0x0b,0xe5,0x0a,0x95,0x0c,0xf5,0x0a,0x90,0x7f,0xb4,0xe0,0x20,0xe2,0x03,0x02},
	16, 0x11d0, 0,  {0x11,0x4c,0x80,0xf4,0x90,0x7f,0xe8,0xe0,0x64,0x40,0x70,0x6e,0xe5,0x0b,0x45,0x0a},
	16, 0x11e0, 0,  {0x60,0x68,0xe4,0x90,0x7f,0xc5,0xf0,0x90,0x7f,0xb4,0xe0,0x20,0xe3,0xf9,0x90,0x7f},
	16, 0x11f0, 0,  {0xc5,0xe0,0x75,0x0c,0x00,0xf5,0x0d,0x90,0x7f,0xe9,0xe0,0xb4,0xa3,0x15,0xae,0x0c},
	16, 0x1200, 0,  {0xaf,0x0d,0xa8,0x09,0xac,0x08,0x7d,0x01,0x7b,0x01,0x7a,0x7e,0x79,0xc0,0x12,0x13},
	16, 0x1210, 0,  {0x56,0x80,0x0f,0xaf,0x09,0xae,0x08,0xad,0x0d,0x7a,0x7f,0x79,0x00,0x7b,0x00,0x12},
	16, 0x1220, 0,  {0x14,0xb9,0xe5,0x0d,0x25,0x09,0xf5,0x09,0xe5,0x0c,0x35,0x08,0xf5,0x08,0xc3,0xe5},
	16, 0x1230, 0,  {0x0b,0x95,0x0d,0xf5,0x0b,0xe5,0x0a,0x95,0x0c,0xf5,0x0a,0x90,0x7f,0xb4,0xe0,0x44},
	10, 0x1240, 0,  {0x02,0xf0,0x80,0x98,0x90,0x7f,0xea,0xe0,0xf5,0x1c},
	1, 	0x124a, 0,  {0x22},
	6,  0x1558, 0,  {0xab,0x07,0xaa,0x06,0xac,0x05},
	16, 0x155e, 0,  {0xe4,0xfd,0x30,0x01,0x11,0xea,0xff,0xae,0x05,0x0d,0xee,0x24,0x00,0xf5,0x82,0xe4},
	16, 0x156e, 0,  {0x34,0xe0,0xf5,0x83,0xef,0xf0,0xeb,0xae,0x05,0x0d,0x74,0x00,0x2e,0xf5,0x82,0xe4},
	16, 0x157e, 0,  {0x34,0xe0,0xf5,0x83,0xeb,0xf0,0xaf,0x05,0x0d,0x74,0x00,0x2f,0xf5,0x82,0xe4,0x34},
	16, 0x158e, 0,  {0xe0,0xf5,0x83,0xec,0xf0,0xaf,0x1c,0x7a,0xe0,0x7b,0x00,0x12,0x17,0x20,0x7f,0x0a},
	5, 	0x159e, 0,  {0x7e,0x00,0x12,0x17,0x3c},
	1,  0x15a3, 0,  {0x22},
	10, 0x14b9, 0,  {0x8e,0x0e,0x8f,0x0f,0x8d,0x10,0x8a,0x11,0x8b,0x12},
	16, 0x14c3,	0,	{0xe4,0xf5,0x13,0xe5,0x13,0xc3,0x95,0x10,0x50,0x20,0x05,0x0f,0xe5,0x0f,0xae,0x0e},
	16,	0x14d3,	0,	{0x70,0x02,0x05,0x0e,0x14,0xff,0xe5,0x12,0x25,0x13,0xf5,0x82,0xe4,0x35,0x11,0xf5},
	10,	0x14e3,	0,	{0x83,0xe0,0xfd,0x12,0x15,0x58,0x05,0x13,0x80,0xd9},
	1,	0x14ed,	0,	{0x22},
	10,	0x15a4,	0,	{0x8e,0x0e,0x8f,0x0f,0x8d,0x10,0x8a,0x11,0x8b,0x12},
	16,	0x15ae,	0,	{0xe4,0xfd,0x30,0x01,0x12,0xe5,0x0e,0xff,0xae,0x05,0x0d,0xee,0x24,0x03,0xf5,0x82},
	16,	0x15be,	0,	{0xe4,0x34,0xe0,0xf5,0x83,0xef,0xf0,0xe5,0x0f,0xae,0x05,0x0d,0x74,0x03,0x2e,0xf5},
	16,	0x15ce,	0,	{0x82,0xe4,0x34,0xe0,0xf5,0x83,0xe5,0x0f,0xf0,0xaf,0x1c,0x7a,0xe0,0x7b,0x03,0x12},
	13,	0x15de,	0,	{0x17,0x20,0xaf,0x1c,0xad,0x10,0xab,0x12,0xaa,0x11,0x12,0x17,0x04},
	1,	0x15eb,	0,	{0x22},
	16,	0x166e,	0,	{0xc0,0xe0,0xc0,0x83,0xc0,0x82,0xc0,0x85,0xc0,0x84,0xc0,0x86,0x75,0x86,0x00,0xd2},
	16,	0x167e,	0,	{0x00,0x53,0x91,0xef,0x90,0x7f,0xab,0x74,0x01,0xf0,0xd0,0x86,0xd0,0x84,0xd0,0x85},
	7,	0x168e,	0,	{0xd0,0x82,0xd0,0x83,0xd0,0xe0,0x32},
	16,	0x1644,	0,	{0xc0,0xe0,0xc0,0x83,0xc0,0x82,0xc0,0x85,0xc0,0x84,0xc0,0x86,0x75,0x86,0x00,0x90},
	16,	0x1654,	0,	{0x7f,0xc4,0xe4,0xf0,0x53,0x91,0xef,0x90,0x7f,0xab,0x74,0x04,0xf0,0xd0,0x86,0xd0},
	10,	0x1664,	0,	{0x84,0xd0,0x85,0xd0,0x82,0xd0,0x83,0xd0,0xe0,0x32},
	16,	0x1695,	0,	{0xc0,0xe0,0xc0,0x83,0xc0,0x82,0xc0,0x85,0xc0,0x84,0xc0,0x86,0x75,0x86,0x00,0x53},
	16,	0x16a5,	0,	{0x91,0xef,0x90,0x7f,0xab,0x74,0x02,0xf0,0xd0,0x86,0xd0,0x84,0xd0,0x85,0xd0,0x82},
	5,	0x16b5,	0,	{0xd0,0x83,0xd0,0xe0,0x32},
	16,	0x16ba,	0,	{0xc0,0xe0,0xc0,0x83,0xc0,0x82,0xc0,0x85,0xc0,0x84,0xc0,0x86,0x75,0x86,0x00,0x53},
	16,	0x16ca,	0,	{0x91,0xef,0x90,0x7f,0xab,0x74,0x10,0xf0,0xd0,0x86,0xd0,0x84,0xd0,0x85,0xd0,0x82},
	5,	0x16da,	0,	{0xd0,0x83,0xd0,0xe0,0x32},
	1,	0x14ff,	0,	{0x32},
	16,	0x16df,	0,	{0xc0,0xe0,0xc0,0x83,0xc0,0x82,0xc0,0x85,0xc0,0x84,0xc0,0x86,0x75,0x86,0x00,0x53},
	16,	0x16ef,	0,	{0x91,0xef,0x90,0x7f,0xab,0x74,0x08,0xf0,0xd0,0x86,0xd0,0x84,0xd0,0x85,0xd0,0x82},
	5,	0x16ff,	0,	{0xd0,0x83,0xd0,0xe0,0x32},
	1,	0x1767,	0,	{0x32},
	1,	0x1768,	0,	{0x32},
	1,	0x1769,	0,	{0x32},
	1,	0x176a,	0,	{0x32},
	1,	0x176b,	0,	{0x32},
	1,	0x176c,	0,	{0x32},
	1,	0x176d,	0,	{0x32},
	1,	0x176e,	0,	{0x32},
	1,	0x176f,	0,	{0x32},
	1,	0x1770,	0,	{0x32},
	1,	0x1771,	0,	{0x32},
	1,	0x1772,	0,	{0x32},
	1,	0x1773,	0,	{0x32},
	1,	0x1774,	0,	{0x32},
	1,	0x1775,	0,	{0x32},
	1,	0x1776,	0,	{0x32},
	3,	0x43,	0,	{0x02,0x15,0x00},
	16,	0x1500, 0,	{0x02,0x16,0x6e,0x00,0x02,0x16,0x95,0x00,0x02,0x16,0x44,0x00,0x02,0x16,0xdf,0x00},
	16,	0x1510,	0,	{0x02,0x16,0xba,0x00,0x02,0x14,0xff,0x00,0x02,0x17,0x67,0x00,0x02,0x17,0x68,0x00},
	16,	0x1520,	0,	{0x02,0x17,0x69,0x00,0x02,0x17,0x6a,0x00,0x02,0x17,0x6b,0x00,0x02,0x17,0x6c,0x00},
	16,	0x1530,	0,	{0x02,0x17,0x6d,0x00,0x02,0x17,0x6e,0x00,0x02,0x17,0x6f,0x00,0x02,0x17,0x70,0x00},
	16,	0x1540,	0,	{0x02,0x17,0x71,0x00,0x02,0x17,0x72,0x00,0x02,0x17,0x73,0x00,0x02,0x17,0x74,0x00},
	8,	0x1550,	0,	{0x02,0x17,0x75,0x00,0x02,0x17,0x76,0x00},
	16,	0x173c,	0,	{0x8e,0x14,0x8f,0x15,0xe5,0x15,0x15,0x15,0xae,0x14,0x70,0x02,0x15,0x14,0x4e,0x60},
	7,	0x174c,	0,	{0x05,0x12,0x14,0xee,0x80,0xee,0x22},
	8,	0x175f,	0,	{0xe4,0xf5,0x1b,0xd2,0xe9,0xd2,0xaf,0x22},
	16,	0x1619,	0,	{0xa9,0x07,0xe5,0x1b,0x70,0x23,0x90,0x7f,0xa5,0xe0,0x44,0x80,0xf0,0xe9,0x25,0xe0},
	16,	0x1629,	0,	{0x90,0x7f,0xa6,0xf0,0x8d,0x16,0xaf,0x03,0xa9,0x07,0x75,0x17,0x01,0x8a,0x18,0x89},
	11,	0x1639,	0,	{0x19,0xe4,0xf5,0x1a,0x75,0x1b,0x01,0xd3,0x22,0xc3,0x22},
	16,	0x15ec,	0,	{0xa9,0x07,0xe5,0x1b,0x70,0x25,0x90,0x7f,0xa5,0xe0,0x44,0x80,0xf0,0xe9,0x25,0xe0},
	16,	0x15fc,	0,	{0x44,0x01,0x90,0x7f,0xa6,0xf0,0x8d,0x16,0xaf,0x03,0xa9,0x07,0x75,0x17,0x01,0x8a},
	13,	0x160c,	0,	{0x18,0x89,0x19,0xe4,0xf5,0x1a,0x75,0x1b,0x03,0xd3,0x22,0xc3,0x22},
	3,	0x4b,	0,	{0x02,0x13,0x7f},
	16,	0x137f,	0,	{0xc0,0xe0,0xc0,0x83,0xc0,0x82,0xc0,0x85,0xc0,0x84,0xc0,0x86,0x75,0x86,0x00,0xc0},
	16,	0x138f,	0,	{0xd0,0x75,0xd0,0x00,0xc0,0x00,0xc0,0x01,0xc0,0x02,0xc0,0x03,0xc0,0x06,0xc0,0x07},
	16,	0x139f,	0,	{0x90,0x7f,0xa5,0xe0,0x30,0xe2,0x06,0x75,0x1b,0x06,0x02,0x14,0x4e,0x90,0x7f,0xa5},
	16,	0x13af,	0,	{0xe0,0x20,0xe1,0x0c,0xe5,0x1b,0x64,0x02,0x60,0x06,0x75,0x1b,0x07,0x02,0x14,0x4e},
	16,	0x13bf,	0,	{0xaf,0x1b,0xef,0x24,0xfe,0x60,0x48,0x14,0x60,0x2c,0x24,0xfe,0x60,0x77,0x24,0x04},
	16,	0x13cf,	0,	{0x60,0x03,0x02,0x14,0x4e,0xab,0x17,0xaa,0x18,0xa9,0x19,0xaf,0x1a,0x05,0x1a,0x8f},
	16,	0x13df,	0,	{0x82,0x75,0x83,0x00,0x12,0x12,0x4b,0x90,0x7f,0xa6,0xf0,0xe5,0x1a,0x65,0x16,0x70},
	16,	0x13ef,	0,	{0x5e,0x75,0x1b,0x05,0x80,0x59,0x90,0x7f,0xa6,0xe0,0xab,0x17,0xaa,0x18,0xa9,0x19},
	16,	0x13ff,	0,	{0xae,0x1a,0x8e,0x82,0x75,0x83,0x00,0x12,0x12,0x78,0x75,0x1b,0x02,0x80,0x40,0xe5},
	16,	0x140f,	0,	{0x16,0x24,0xfe,0xb5,0x1a,0x07,0x90,0x7f,0xa5,0xe0,0x44,0x20,0xf0,0xe5,0x16,0x14},
	16,	0x141f,	0,	{0xb5,0x1a,0x0a,0x90,0x7f,0xa5,0xe0,0x44,0x40,0xf0,0x75,0x1b,0x00,0x90,0x7f,0xa6},
	16,	0x142f,	0,	{0xe0,0xab,0x17,0xaa,0x18,0xa9,0x19,0xae,0x1a,0x8e,0x82,0x75,0x83,0x00,0x12,0x12},
	16,	0x143f,	0,	{0x78,0x05,0x1a,0x80,0x0a,0x90,0x7f,0xa5,0xe0,0x44,0x40,0xf0,0x75,0x1b,0x00,0x53},
	16,	0x144f,	0,	{0x91,0xdf,0xd0,0x07,0xd0,0x06,0xd0,0x03,0xd0,0x02,0xd0,0x01,0xd0,0x00,0xd0,0xd0},
	13,	0x145f,	0,	{0xd0,0x86,0xd0,0x84,0xd0,0x85,0xd0,0x82,0xd0,0x83,0xd0,0xe0,0x32},
	16,	0x1704,	0,	{0x12,0x15,0xec,0xe5,0x1b,0x24,0xfa,0x60,0x0e,0x14,0x60,0x06,0x24,0x07,0x70,0xf3},
	12,	0x1714,	0,	{0xd3,0x22,0xe4,0xf5,0x1b,0xd3,0x22,0xe4,0xf5,0x1b,0xd3,0x22},
	16,	0x1720,	0,	{0x12,0x16,0x19,0xe5,0x1b,0x24,0xfa,0x60,0x0e,0x14,0x60,0x06,0x24,0x07,0x70,0xf3},
	12,	0x1730,	0,	{0xd3,0x22,0xe4,0xf5,0x1b,0xd3,0x22,0xe4,0xf5,0x1b,0xd3,0x22},
	16,	0x14ee,	0,	{0x74,0x00,0xf5,0x86,0x90,0xfd,0xa5,0x7c,0x05,0xa3,0xe5,0x82,0x45,0x83,0x70,0xf9},
	1,	0x14fe,	0,	{0x22},
	3,	0x0,	0,	{0x02,0x17,0x53},
	12,	0x1753,	0,	{0x78,0x7f,0xe4,0xf6,0xd8,0xfd,0x75,0x81,0x20,0x02,0x14,0x6c},
	16,	0x124b,	0,	{0xbb,0x01,0x0c,0xe5,0x82,0x29,0xf5,0x82,0xe5,0x83,0x3a,0xf5,0x83,0xe0,0x22,0x50},
	16,	0x125b,	0,	{0x06,0xe9,0x25,0x82,0xf8,0xe6,0x22,0xbb,0xfe,0x06,0xe9,0x25,0x82,0xf8,0xe2,0x22},
	13,	0x126b,	0,	{0xe5,0x82,0x29,0xf5,0x82,0xe5,0x83,0x3a,0xf5,0x83,0xe4,0x93,0x22},
	16,	0x1278,	0,	{0xf8,0xbb,0x01,0x0d,0xe5,0x82,0x29,0xf5,0x82,0xe5,0x83,0x3a,0xf5,0x83,0xe8,0xf0},
	16,	0x1288,	0,	{0x22,0x50,0x06,0xe9,0x25,0x82,0xc8,0xf6,0x22,0xbb,0xfe,0x05,0xe9,0x25,0x82,0xc8},
	2,	0x1298,	0,	{0xf2,0x22},
	16, 0x129a,	0,	{0xe7,0x09,0xf6,0x08,0xdf,0xfa,0x80,0x46,0xe7,0x09,0xf2,0x08,0xdf,0xfa,0x80,0x3e},
	16,	0x12aa,	0,	{0x88,0x82,0x8c,0x83,0xe7,0x09,0xf0,0xa3,0xdf,0xfa,0x80,0x32,0xe3,0x09,0xf6,0x08},
	16,	0x12ba,	0,	{0xdf,0xfa,0x80,0x6e,0xe3,0x09,0xf2,0x08,0xdf,0xfa,0x80,0x66,0x88,0x82,0x8c,0x83},
	16,	0x12ca,	0,	{0xe3,0x09,0xf0,0xa3,0xdf,0xfa,0x80,0x5a,0x89,0x82,0x8a,0x83,0xe0,0xa3,0xf6,0x08},
	16,	0x12da,	0,	{0xdf,0xfa,0x80,0x4e,0x89,0x82,0x8a,0x83,0xe0,0xa3,0xf2,0x08,0xdf,0xfa,0x80,0x42},
	16,	0x12ea,	0,	{0x80,0xd2,0x80,0xfa,0x80,0xc6,0x80,0xd4,0x80,0x55,0x80,0xf2,0x80,0x29,0x80,0x10},
	16,	0x12fa,	0,	{0x80,0xa6,0x80,0xea,0x80,0x9a,0x80,0xa8,0x80,0xda,0x80,0xe2,0x80,0xca,0x80,0x29},
	16,	0x130a,	0,	{0x88,0x84,0x8c,0x85,0x89,0x82,0x8a,0x83,0xe4,0x93,0xa3,0x05,0x86,0xf0,0xa3,0x05},
	16,	0x131a,	0,	{0x86,0xdf,0xf5,0xde,0xf3,0x80,0x0b,0x89,0x82,0x8a,0x83,0xe4,0x93,0xa3,0xf6,0x08},
	16,	0x132a,	0,	{0xdf,0xf9,0xec,0xfa,0xa9,0xf0,0xed,0xfb,0x22,0x88,0x84,0x8c,0x85,0x89,0x82,0x8a},
	16,	0x133a,	0,	{0x83,0xe0,0xa3,0x05,0x86,0xf0,0xa3,0x05,0x86,0xdf,0xf6,0xde,0xf4,0x80,0xe3,0x89},
	16,	0x134a,	0,	{0x82,0x8a,0x83,0xe4,0x93,0xa3,0xf2,0x08,0xdf,0xf9,0x80,0xd6,0x88,0xf0,0xed,0x24},
	16,	0x135a,	0,	{0x02,0xb4,0x04,0x00,0x50,0xcc,0xf5,0x82,0xeb,0x24,0x02,0xb4,0x04,0x00,0x50,0xc2},
	16,	0x136a,	0,	{0x23,0x23,0x45,0x82,0xf5,0x82,0xef,0x4e,0x60,0xb8,0xef,0x60,0x01,0x0e,0xe5,0x82},
	5,	0x137a,	0,	{0x23,0x90,0x12,0xea,0x73},
	0,	0x0,	1,	{0}
};
