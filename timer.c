#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include "VideoCard.h"


int sub_int_timer(int *hook_id){
	int IRQLINE=0;
	int IRQPOLICY=IRQ_REENABLE;
	*hook_id=0;
	sys_irqsetpolicy(IRQLINE,IRQPOLICY,hook_id);
	sys_irqenable(hook_id);
	return 1;
}

int unsub_int_timer(int *hook_id){
	sys_irqdisable(hook_id);
	sys_irqrmpolicy(hook_id);
	return 1;
}

int timed( double time){
	unsigned int inter=0;
	int hook_id=0;
	int ipc_status;
	int r;
	int irq_set=BIT(0);
	sub_int_timer(&hook_id);
	message msg;
	while(!(inter>=(time*17))){
	if((r=driver_receive(ANY,&msg,&ipc_status))!=0){
				printf("Driver Receive Failure WIth:%d\n",r);
				continue;
			}
			if(is_ipc_notify(ipc_status)){
				switch(_ENDPOINT_P(msg.m_source)){
				case HARDWARE:
					if(msg.NOTIFY_ARG &irq_set){
						inter++;
					}
					break;
				default:
					break;
				}
			}else{
				printf("IPC_STATUS ERROR!\n");
		}
	}
	unsub_int_timer(&hook_id);
	return 1;
}
