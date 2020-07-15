#ifndef __MS_H
#define __MS_H

//Define Related File

//#define BIT(n) (0x01<<(n))
//ports
#define IO_BUFFER 0x60
#define Controller 0x64
//commands
#define Read_Command_Byte 0x20 //command byte
#define Write_Command_Byte 0x60 //command Byte
#define Disable_Mouse 0xA7
#define Enable_Mouse 0xA8
#define Check_Mouse_Interface 0xA9 //returns 0 if OK
#define Write_Byte_Mouse 0xD4//Byte(A)
//KBC Command Byte
#define Mouse_OBF BIT(1)
#define Keyboard_OBF BIT(0)
#define Disable_Mouse_ BIT(5)
#define Disable_Keyboard BIT(4)
//PS/2 Mouse Commands
#define RESET 0xFF
#define RESEND 0xFE
#define SET_DEFAULT 0xF6
#define DISABLE_DATA_REPORTING 0xF5 //In stream mode, should be sent before any other command
#define ENABLE_DATA_REPORTING 0xF4 //In Stream Mode Only
#define SET_SAMPLE_RATE 0xF3
#define SET_REMOTE_MODE 0xF0
#define READ_DATA 0xEB //SEND DATA PACKET REQUESTS(prolly related with remote mode)
#define SET_STREAM_MODE 0xEA
#define STATUS_REQUEST 0xE9
#define SET_RESOLUTION 0xE8
#define SET_SCALING_ACELERATION 0xE7 //2:1
#define SET_SCALLING_LINEAR 0xE6 //1:1
//acknowledgment byte
#define ACK 0xFA //everything is OK
#define NACK 0xFE//invalid byte might be serial communication error
#define ERROR 0xFC//second consecutive invalid byte

#endif
