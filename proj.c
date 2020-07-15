#pragma once
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
#include<stdio.h>
#include"test5.h"
#include"video_gr.h"
#include "vbe.h"
#include "timer.h"
#include "mouse.h"
#include "VideoCard.h"
#include "MS.h"
#include "keyboard.c"
#include "sprite.h"
#include <math.h>
#include "Projectile.h"
#include <stdlib.h>
#include <time.h>

#define MAX_BULLETS 5

int main(int argc, char **argv) {
	srand(time(NULL));
	sef_startup();
	vg_init(101);
	map_vram();
	Wall walls[6];
	int l;
	for (l = 0; l < 6; l++) {
		walls[l] = New_Wall();
	}
	Enemy* enemies[20];
	for (l = 0; l < 20; l++) {
		Enemy enemie = New_Enemy();
		enemies[l] = malloc(sizeof(enemie));
		enemies[l]->x = enemie.x;
		enemies[l]->y = enemie.y;
	}
	Projectile* bullets[MAX_BULLETS];
	int c;
	for (c = 0; c < MAX_BULLETS; c++) {
		bullets[c] = NULL;
	}
	int current_x = 320;
	int current_y = 240;
	int mov_x = 320;
	int mov_y = 240;
	long unsigned int data;
	unsigned int try = 0;
	int type = 0;
	SPRITE sprite;
	int useTimer = 0;
	int timercounter = 0;
	int difx;
	int dify;
	float slope;
	double bulletx;
	double bullety;
	int b;
	unsigned short pixelData[480][640];
	sprite = loadBitmap("home/lcom/proj/src/LCOM.bmp", &pixelData);
	int i = 0;
	int j = 0;
	unsigned int trigger;
	unsigned int hook_id = 12;
	unsigned int kbd_hook = 1;
	unsigned int timer_hook = 0;
	double angle = 0;
	int n_en = 20;
	sys_inb(IO_BUFFER, &data);
	mouse_sub_int(&hook_id);
	sub_int_timer(&timer_hook);
	kbc_sub_int(&kbd_hook);
	srand(time(NULL));
	int rando;
	if (enable_mouse()) {
		int ipc_status;
		int r;
		int irq_set12 = BIT(12);
		int irq_set0 = BIT(0);
		int irq_set1 = BIT(1);
		message msg;
		int x = 0;
		int y = 0;
		int count = 0;
		while (try != 1000 * 3) {
			if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
				printf("Driver Receive Failure WIth:%d\n", r);
				//continue;
			}
			if (is_ipc_notify(ipc_status)) {
				switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE:
					if (msg.NOTIFY_ARG & irq_set12) {
						if (type > 0) {
							readMouse(&x, &y, &count, &trigger);
							if (count == 3) {
								current_x += x;
								current_y += y;
								if (current_x < 0) {
									current_x = 0;
								}
								if (current_y < 0) {
									current_y = 0;
								}
								if (current_x >= 640) {
									current_x = 639;
								}
								if (current_y >= 480) {
									current_y = 479;
								}
								if (trigger == 1) {
									useTimer = 1;
									Projectile entitie;
									entitie = New_Projectile(current_x,
											current_y, mov_x, mov_y);
									int y = 0;
									int found = 0;
									int notNull = 0;
									for (y = 0; y < MAX_BULLETS; y++) {
										if ((bullets[y] == NULL)
												&& (found == 0)) {
											(bullets[y]) = malloc(
													sizeof(Projectile));
											bullets[y]->BulletXpos =
													entitie.BulletXpos;
											bullets[y]->BulletYpos =
													entitie.BulletYpos;
											bullets[y]->BulletXSpeed =
													entitie.BulletXSpeed;
											bullets[y]->BulletYSpeed =
													entitie.BulletYSpeed;
											found = 1;
											printf("Entitie Added\n");
											char buffer[200];
										}
									}
									printf("Number OF Entities : %d\n",
											notNull);
									found = 0;
									trigger = 0;
									notNull = 0;
								}
								printf("Sight-Reticle Position: (%d,%d)\n",
										current_x, current_y);
							}
						} else {
							sys_inb(0x60, &data);
							type++;
						}
					}
					if (msg.NOTIFY_ARG & irq_set1) {
						unsigned int med;
						med = read_kbc();
						if (med == 0) {
							try = 1000 * 3;
							printf(
									"\n\n EXITING APLICATION ... \n APLICATION FINISHED \n\n");
							continue;
						}
						if (med == 2) {
							mov_x -= 2;
						}
						if (med == 4) {
							mov_x += 2;
						}
						if (med == 1) {
							mov_y -= 2;
						}
						if (med == 3) {
							mov_y += 2;
						}
						current_x += x;
						current_y += y;
						if (current_x < 0) {
							current_x = 0;
						}
						if (current_y < 0) {
							current_y = 0;
						}
						if (current_x >= 640) {
							current_x = 639;
						}
						if (current_y >= 480) {
							current_y = 479;
						}
						printf("Player Character Position: (%d,%d)\n", mov_x,
								mov_y);
					}
					if (msg.NOTIFY_ARG & irq_set0) {
						clear_screen();
						showScreen();
						rando = rand();
						DrawWall(walls);
						DrawEnemy(enemies);
						for (i = 0; i < MAX_BULLETS; i++) {
							if (!(bullets[i] == NULL)) {
								int xx, yy;
								xx = (int) (bullets[i]->BulletXpos);
								yy = (int) (bullets[i]->BulletYpos);
								printf("Bullet %d Pos:(%d,%d)\n", i, xx, yy);
								draw_pixel(xx, yy, 0xF800);
								draw_pixel(xx + 1, yy, 0xF800);
								draw_pixel(xx + 2, yy, 0x07E0);
								draw_pixel(xx - 1, yy, 0xF800);
								draw_pixel(xx - 2, yy, 0x07E0);
								draw_pixel(xx, yy + 1, 0xF800);
								draw_pixel(xx, yy + 2, 0x07E0);
								draw_pixel(xx, yy - 1, 0xF800);
								draw_pixel(xx, yy - 2, 0x07E0);
								draw_pixel(xx - 1, yy - 1, 0x07E0);
								draw_pixel(xx + 1, yy - 1, 0x07E0);
								draw_pixel(xx + 1, yy + 1, 0x07E0);
								draw_pixel(xx - 1, yy + 1, 0x07E0);
							}
						}
						for (i = 0; i < MAX_BULLETS; i++) {
							if (!(bullets[i] == NULL)) {
								int remove = 0;
								int en = 0;
								remove = BulletWallColision((*bullets[i]),
										walls);
								en = BulletEnemyColision((*bullets[i]),
										enemies);
								bullets[i]->BulletXpos +=
										bullets[i]->BulletXSpeed;
								bullets[i]->BulletYpos +=
										bullets[i]->BulletYSpeed;
								if (remove == 1) {
									free(bullets[i]);
									bullets[i] = NULL;
								}
								if (en != 0) {
									free(enemies[en - 1]);
									free(bullets[i]);
									bullets[i]=NULL;
									enemies[en - 1] = NULL;
									n_en--;
								}
							}
						}
						for (i = 0; i < MAX_BULLETS; i++) {
							int xx, yy;
							if (!(bullets[i] == NULL)) {
								xx = (int) (bullets[i]->BulletXpos);
								yy = (int) (bullets[i]->BulletYpos);
								if (xx < 0 || xx >= 640) {
									free(bullets[i]);
									bullets[i] = NULL;
								}
								if (yy < 0 || yy >= 480) {
									free(bullets[i]);
									bullets[i] = NULL;
								}
							}
						}

						for (i = 0; i < 200; i++) {
							for (j = 0; j < 200; j++) {
								draw_pixel(mov_x + j - 11, mov_y + i - 11,
										sprite.pixelData[i][j]);
							}
						}

						draw_pixel(current_x, current_y, 0xF800);
						draw_pixel(current_x + 1, current_y, 0x07E0);
						draw_pixel(current_x + 2, current_y, 0x07E0);
						draw_pixel(current_x, current_y + 1, 0x07E0);
						draw_pixel(current_x, current_y + 2, 0x07E0);
						draw_pixel(current_x - 1, current_y, 0x07E0);
						draw_pixel(current_x - 2, current_y, 0x07E0);
						draw_pixel(current_x, current_y - 1, 0x07E0);
						draw_pixel(current_x, current_y - 2, 0x07E0);
						draw_pixel(current_x - 3, current_y, 0x07E0);
						draw_pixel(current_x + 3, current_y, 0x07E0);
						draw_pixel(current_x, current_y - 3, 0x07E0);
						draw_pixel(current_x, current_y + 3, 0x07E0);
						draw_pixel(current_x - 1, current_y + 3, 0x07E0);
						draw_pixel(current_x - 2, current_y + 2, 0x07E0);
						draw_pixel(current_x - 3, current_y + 1, 0x07E0);
						draw_pixel(current_x + 1, current_y + 3, 0x07E0);
						draw_pixel(current_x + 2, current_y + 2, 0x07E0);
						draw_pixel(current_x + 3, current_y + 1, 0x07E0);
						draw_pixel(current_x + 1, current_y - 3, 0x07E0);
						draw_pixel(current_x + 2, current_y - 2, 0x07E0);
						draw_pixel(current_x + 3, current_y - 1, 0x07E0);
						draw_pixel(current_x - 1, current_y - 3, 0x07E0);
						draw_pixel(current_x - 2, current_y - 2, 0x07E0);
						draw_pixel(current_x - 3, current_y - 1, 0x07E0);
						x = 0;
						y = 0;
						if (n_en == 0) {
							try = 1000 * 3;
						}
					}
					break;
				default:
					break;
				}
			}
		}
	}

	for (i = 0; i < MAX_BULLETS; i++) {
		free(bullets[i]);
		bullets[i] = NULL;
	}
	for (i = 0; i < 20; i++) {
		free(enemies[i]);
		enemies[i] = NULL;
	}
	sys_outb(Controller, Write_Byte_Mouse);
	sys_outb(IO_BUFFER, DISABLE_DATA_REPORTING);
	unsub_int_timer(&timer_hook);
	kbc_unsub_int(&kbd_hook);
	sys_inb(IO_BUFFER, &data);
	mouse_unsub_int(&hook_id);
	sys_inb(IO_BUFFER, &data);
	vg_exit();
	return 1;
}
