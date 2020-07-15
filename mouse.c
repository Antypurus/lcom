#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include "VideoCard.h"
#include "MS.h"

unsigned int read_state = 1;
unsigned int X_Carry_Bit;
unsigned int Y_Carry_Bit;
unsigned int Xoverflow;
unsigned int Yoverflow;
int YDelta = 0;
int XDelta = 0;
unsigned int YCounter = 0;
unsigned int right_pressed = 0;
unsigned int middle_pressed = 0;
unsigned int left_pressed = 0;
unsigned int bytes[3];

int enable_mouse() {
	long unsigned int data;
	sys_outb(Controller, Write_Byte_Mouse);
	sys_outb(IO_BUFFER, ENABLE_DATA_REPORTING);
	sys_inb(IO_BUFFER, &data);
	if (data == 0xFA) {
		printf("Mouse activated\n");
		return 1;
	} else {
		if (data == NACK) {
			printf("Resending Mouse Enable command...\n");
			enable_mouse();
		} else {
			printf("Mouse Enabling Error\n");
			return 0;
		}
	}
}

int get_bit(int Number, int Wanted_Bit) {
	unsigned int result_bit;
	unsigned int bit_mask = (1 << Wanted_Bit);
	unsigned int Masked_Bit = (Number & bit_mask);
	result_bit = Masked_Bit >> Wanted_Bit;
	return result_bit;
}

int mouse_sub_int(unsigned int *hook_id) {
	int IRQ_Policy = IRQ_REENABLE | IRQ_EXCLUSIVE;
	sys_irqsetpolicy(12, IRQ_Policy, hook_id);
	sys_irqenable(hook_id);
	return 1;
}

int mouse_unsub_int(unsigned int *hook_id) {
	sys_irqrmpolicy(hook_id);
	sys_irqdisable(hook_id);
	return 1;
}

int readMouse(int *x, int*y, int *count,int *rm) {
	int ready = 0;
	int data;
	sys_inb(IO_BUFFER, &data);
	//printf("\n0x%d\n\n",data);
	unsigned int bit0 = get_bit(data, 0);
	unsigned int bit1 = get_bit(data, 1);
	unsigned int bit2 = get_bit(data, 2);
	unsigned int bit4 = get_bit(data, 4);
	unsigned int bit5 = get_bit(data, 5);
	unsigned int bit6 = get_bit(data, 6);
	unsigned int bit7 = get_bit(data, 7);
	*count=read_state;
	switch (read_state) {
	case (1):
		//printf("1\n");
		bytes[0] = data;
		read_state = 2;
		X_Carry_Bit = bit4;
		Y_Carry_Bit = bit5;
		if(bit0==1){
			*rm=1;
		}
		break;
	case (2):
		//printf("2\n");
		bytes[1] = data;
		read_state = 3;
		if (X_Carry_Bit == 1) {
			XDelta = -(~data+256);
		} else {
			XDelta = data;
		}
		//printf("XDELTA:%d\n", XDelta);
		break;
	case (3):
		//printf("3\n");
		bytes[2] = data;
		read_state = 1;
		if (Y_Carry_Bit == 1) {
			//printf("data:%d\n",data);
			YDelta = -(~data+256);
			//printf("YDELta:%d\n",YDelta);
		} else {
			//printf("data:%d\n",data);
			YDelta = data;
			//printf("YDELta:%d\n",YDelta);
		}
		//printf("YDELTA:%d\n", YDelta);
		*x = XDelta;
		*y = -YDelta;
		break;
	}
	return 1;
}

