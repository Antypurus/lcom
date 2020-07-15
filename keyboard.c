#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>


void kbc_sub_int(int *hook) {
	int IRQPOLICY = IRQ_REENABLE | IRQ_EXCLUSIVE;
	sys_irqsetpolicy(1, IRQPOLICY, hook);
	sys_irqenable(hook);
}

void kbc_unsub_int(int *hook) {
	sys_irqdisable(hook);
	sys_irqrmpolicy(hook);
}

int read_kbc() {
	int data;
	sys_inb(0x60, &data);
	switch (data) {
	case (0x11):
		return 1; //w
		break;
	case (0x1E):
		return 2; //a
		break;
	case (0x1F):
		return 3; //s
		break;
	case (0x20):
		return 4; //d
		break;
	case (0x81):
		return 0; //esc
		break;
	default:
		break;
	}
	//return data;
}
