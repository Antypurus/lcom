void *test_init(unsigned short mode, unsigned short delay) {
	
	sef_startup();
	vg_init(101);
	map_vram();
	sleep(5);
	vg_exit();
	printf("VRAM ADRESS:0x%x",getVMadrs());
	/* To be completed */
	
}


int test_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color) {
	sef_startup();
	vg_init(101);
	map_vram();
	drawCircle(0,0,50,100);
	sleep(5);
	vg_exit();
	/* To be completed */
	
}

int test_line(unsigned short xi, unsigned short yi, 
		           unsigned short xf, unsigned short yf, unsigned long color) {
	sef_startup();
		vg_init(101);
		map_vram();
		drawCircle(0,0,50,100);
		sleep(5);
		vg_exit();
	/* To be completed */
	
}

int test_xpm(unsigned short xi, unsigned short yi, char *xpm[]) {
	
	/* To be completed */
	
}	

int test_move(unsigned short xi, unsigned short yi, char *xpm[], 
				unsigned short hor, short delta, unsigned short time) {
	
	/* To be completed */
	
}					

int test_controller() {
	
	/* To be completed */
	
}					
	
