#ifndef __VIDEOCARD_H
#define __VIDEOCARD_H

#define BIT(x)	(0x01<<x)

//function responses
#define FAILED 0x01 //Function call failed
#define UNSOPORTED 0x02 //Function is not supported in the current hardware configuration
#define INVALID 0x03 //Function is invalid in the current video mode
//graphics mode setting
#define G640x480 0x101
#define G800x600 0x103
#define G1024x768 0x105
#define G1280x1024 0x107
//video card functions
#define SET_VIDEO_MODE 0x02 //must be passed in the BX register

#define HardAdress 0xE0000000 //vram address for my pc
//BIOS SERVICES
#define VIDEO_CARD 10h
#define PC_CONFIGURATION 11h
#define MEMORY_CONFIGURATION 12h
#define KEYBOARD 16h

#endif
