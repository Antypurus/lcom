
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
#include "vbe.h"
#include "VideoCard.h"
#include "sprite.h"
/* Constants for VBE 0x105 mode */

/* The physical address may vary from VM to VM.
 * At one time it was 0xD0000000
 *  #define VRAM_PHYS_ADDR    0xD0000000 
 * Currently on lab B107 is 0xF0000000
 * Better run my version of lab5 as follows:
 *     service run `pwd`/lab5 -args "mode 0x105"
 */
#define VRAM_PHYS_ADDR	0xE0000000
#define H_RES             640
#define V_RES		  480
#define BITS_PER_PIXEL	  8


/* Private global variables */

 short *Video_mem;		/* Process address to which VRAM is mapped */
 short *VRAM[V_RES][H_RES];
 short VRAM_BUFFER_2[V_RES][H_RES];
 short VRAM_BUFFER_1[V_RES*H_RES];
 short BLANCK[V_RES*H_RES];


static unsigned h_res=H_RES;		/* Horizontal screen resolution in pixels */
static unsigned v_res=V_RES;		/* Vertical screen resolution in pixels */
static unsigned bits_per_pixel=BITS_PER_PIXEL; /* Number of VRAM bits per pixel */


short* getFrameBuffer(){
	return &Video_mem;
}

void drawCircle(int x1,int x2,int y1,int y2){
		int i=0;
		for(i=0;i<10000000;i++){
			Video_mem[i]=1;
			//if(h_res/i>y1&&h_res/i<y2){
				Video_mem[i]=2;
			//}
		}
		sleep(2);
		vg_exit();
}
void map_vram(){
	int r;
	struct mem_range mr;
	unsigned int vram_base=HardAdress; /* VRAM’s physical addresss */
	unsigned int vram_size=H_RES*V_RES*16; /* VRAM’s size, but you can use
	*/
	/*the frame-buffer size, instead */

	void *video_mem; /* frame-buffer VM address */

	/* Allow memory mapping */

	mr.mr_base = (phys_bytes) vram_base;
	mr.mr_limit = mr.mr_base + vram_size;
	int i=0;
	if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
	panic("sys_privctl (ADD_MEM) failed: %d\n", r);
	/* Map memory */
	video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);
	if(video_mem == MAP_FAILED)
	panic("couldn’t map video memory");
	Video_mem=video_mem;
	int try=0;
	int j=0;
	for(i=0;i<V_RES;i++){
		for(j=0;j<H_RES;j++){
			VRAM[i][j]=&(Video_mem[try]);
			VRAM_BUFFER_2[i][j]=0;
			VRAM_BUFFER_1[i*H_RES+j+1]=0;
			try++;
		}
	}
	for(i=0;i<V_RES*H_RES;i++){
		BLANCK[i]=0;
	}
	printf("VRAM Bidimensional Mapping Complete\n");

}


void * getVMadrs(){
	return Video_mem;
}
int vg_exit() {
  struct reg86u reg86;

  reg86.u.b.intno = 0x10; /* BIOS video services */

  reg86.u.b.ah = 0x00;    /* Set Video Mode function */
  reg86.u.b.al = 0x03;    /* 80x25 text mode*/



  if( sys_int86(&reg86) != OK ) {
      printf("\tvg_exit(): sys_int86() failed \n");
      return 1;
  } else
      return 0;
}

void *vg_init(unsigned short mode){
	struct reg86u reg86;
	int s;
	printf("vram size:");
	scanf("%d",&s);

	  reg86.u.b.intno = 0x10;

	  reg86.u.w.ax=0x4F02;
	  reg86.u.w.bx=1<<14|0x111;
	  if( sys_int86(&reg86) != OK ) {
	        printf("\tvg_exit(): sys_int86() failed \n");
	    } else{
	    	printf("entered something mode\n");
	    	//map_vram();
	    	}
}

int color=0;
void clear_screen(){
	int i;
	int j;
	for(i=0;i<V_RES;i++){
		for(j=0;j<H_RES;j++){
			(VRAM_BUFFER_2[i][j])=0;
		}
	}
	memcpy(Video_mem,BLANCK,H_RES*V_RES*2);
}


int draw_pixel(int x,int y , int color){
	if(x<0||x>=H_RES){
		return 0;
	}
	if(y<0||y>=V_RES){
		return 0 ;
	}
	int i=color;
	if(i==0){
		return 0;
	}
	//(Video_mem[y*H_RES+x+1])=color;
	(VRAM_BUFFER_1[y*H_RES+x+1])=color;
	return 1;
}

int ToBuffer1(){
	int i,j;
	for(i=0;i<480;i++){
		for(j=0;j<640;j++){
			VRAM_BUFFER_1[i*H_RES+j+1]=VRAM_BUFFER_2[i][j];
		}
	}
}

int showScreen(){
	memcpy(Video_mem,VRAM_BUFFER_1,H_RES*V_RES*2);
	memcpy(VRAM_BUFFER_1,BLANCK,H_RES*V_RES*2);
}



