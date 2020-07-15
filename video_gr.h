#ifndef __VIDEO_GR_H
#define __VIDEO_GR_H
#include "sprite.h"

short* getFrameBuffer();

/** @defgroup video_gr video_gr
 * @{
 *
 * Functions for outputing data to screen in graphics mode
 */

/**
 * @brief Initializes the video module in graphics mode
 * 
 * Uses the VBE INT 0x10 interface to set the desired
 *  graphics mode, maps VRAM to the process' address space and
 *  initializes static global variables with the resolution of the screen, 
 *  and the number of colors
 * 
 * @param mode 16-bit VBE mode to set
 * @return Virtual address VRAM was mapped to. NULL, upon failure.
 */
void *vg_init(unsigned short mode);

 /**
 * @brief Returns to default Minix 3 text mode (0x03: 25 x 80, 16 colors)
 * 
 * @return 0 upon success, non-zero upon failure
 */
int vg_exit(void);

 /** @} end of video_gr */
void map_vram();
void drawCircle(int x1,int x2,int y1,int y2);
void clear_screen();
int draw_pixel(int x,int y , int color);
int ToBuffer1();
int showScreen();

#endif /* __VIDEO_GR_H */
