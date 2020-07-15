#pragma once

#include <math.h>
#include "Projectile.h"
#include "video_gr.h"
#include <stdio.h>

Projectile New_Projectile(int MouseXpos, int MouseYpos, int PlayerXpos,
		int PlayerYpos) {
	int DiffX = MouseXpos - PlayerXpos;
	int DiffY = MouseYpos - PlayerYpos;
	int BulletSpeed = 10;
	double angle = atan2(DiffY, DiffX);
	double BulletXSpeed = BulletSpeed * cos(angle);
	double BulletYSpeed = BulletSpeed * sin(angle);
	char buffer[200];
	Projectile projectile;
	projectile.angle = angle;
	projectile.BulletXpos = PlayerXpos;
	projectile.BulletYpos = PlayerYpos;
	projectile.BulletSpeed = BulletSpeed;
	projectile.BulletXSpeed = BulletXSpeed;
	projectile.BulletYSpeed = BulletYSpeed;
	projectile.isVoid = 0;
	if (projectile.isVoid == 0) {
		return projectile;
	}
	return projectile;
}

Wall New_Wall() {
	int x = rand() % 640;
	int y = rand() % 480;
	int rot = rand() % 2;
	Wall wall;
	wall.x = x;
	wall.y = y;
	wall.Orientation = rot;
	int XRange = 50;
	int YRange = 2;
	wall.XRange = XRange;
	wall.YRange = YRange;
	return wall;
}

void DrawWall(Wall *wall) {
	int i, j, k;
	for (k = 0; k < 6; k++) {
		for (i = 0; i < 480; i++) {
			for (j = 0; j < 640; j++) {
				if (wall[k].Orientation == 0) {
					if ((j >= (wall[k].x - wall[k].XRange))
							&& (j <= (wall[k].x + wall[k].XRange))) {
						if ((i >= (wall[k].y - wall[k].YRange))
								&& (i <= (wall[k].y + wall[k].YRange))) {
							draw_pixel(j, i, 0x001F);
						}
					}
				}
				if (wall[k].Orientation == 1) {
					if ((j >= (wall[k].x - wall[k].YRange))
							&& (j <= (wall[k].x + wall[k].YRange))) {
						if ((i >= (wall[k].y - wall[k].XRange))
								&& (i <= (wall[k].y + wall[k].XRange))) {
							draw_pixel(j, i, 0x001F);
						}
					}
				}
			}
		}
	}
}

Enemy New_Enemy() {
	int x = rand() % 640;
	int y = rand() % 480;
	Enemy enemy;
	enemy.x = x;
	enemy.y = y;
	return enemy;
}

void DrawEnemy(Enemy *enemy[]) {
	int k;
	for (k = 0; k < 20; k++) {
		if (!(enemy[k]==NULL)) {
			int x = enemy[k]->x;
			int y = enemy[k]->y;
			draw_pixel(x, y, 0xFFFF);
			draw_pixel(x + 2, y, 0xFFFF);
			draw_pixel(x + 3, y, 0xFFFF);
			draw_pixel(x - 2, y, 0xFFFF);
			draw_pixel(x - 3, y, 0xFFFF);
			draw_pixel(x - 3, y - 1, 0xFFFF);
			draw_pixel(x - 2, y - 1, 0xFFFF);
			draw_pixel(x + 2, y - 1, 0xFFFF);
			draw_pixel(x + 3, y - 1, 0xFFFF);
			draw_pixel(x, y - 1, 0xFFFF);
			draw_pixel(x - 2, y - 2, 0xFFFF);
			draw_pixel(x - 1, y - 2, 0xFFFF);
			draw_pixel(x, y - 2, 0xFFFF);
			draw_pixel(x + 1, y - 2, 0xFFFF);
			draw_pixel(x + 2, y - 2, 0xFFFF);
			draw_pixel(x - 2, y + 1, 0xFFFF);
			draw_pixel(x - 1, y + 1, 0xFFFF);
			draw_pixel(x, y + 1, 0xFFFF);
			draw_pixel(x + 1, y + 1, 0xFFFF);
			draw_pixel(x + 2, y + 1, 0xFFFF);
			draw_pixel(x - 1, y + 2, 0xFFFF);
			draw_pixel(x, y + 2, 0xFFFF);
			draw_pixel(x + 1, y + 2, 0xFFFF);
			draw_pixel(x - 1, y + 3, 0xFFFF);
			draw_pixel(x, y + 3, 0xFFFF);
			draw_pixel(x + 1, y + 3, 0xFFFF);
		}
	}
}

int BulletWallColision(Projectile bullet, Wall *walls) {
	int i, j, k;
	int x, y;
	x = (int) bullet.BulletXpos;
	y = (int) bullet.BulletYpos;
	double dx = bullet.BulletXSpeed;
	double dy = bullet.BulletXSpeed;
	int lower_x, lower_y, upper_x, upper_y;
	int ori;
	for (k = 0; k < 6; k++) {
		ori = walls[k].Orientation;
		if (ori == 0) {
			lower_x = walls[k].x - walls[k].XRange;
			lower_y = walls[k].y - walls[k].YRange;
			upper_x = walls[k].x + walls[k].XRange;
			upper_y = walls[k].y + walls[k].YRange;
		} else {
			lower_x = walls[k].x - walls[k].YRange;
			lower_y = walls[k].y - walls[k].XRange;
			upper_x = walls[k].x + walls[k].YRange;
			upper_y = walls[k].y + walls[k].XRange;
		}

		if (dy > 0) {
			for (i = 0; i <= dy; i++) {
				if (dx > 0) {
					for (j = 0; j <= dx; j++) {
						if (((x + j) >= lower_x) && ((x + j) <= upper_x)) {
							if (((y + i) >= lower_y) && ((y + i) <= upper_y)) {
								return 1;
							}
						}
					}
				} else {
					for (j = 0; j <= -dx; j++) {
						if (((x - j) >= lower_x) && ((x - j) <= upper_x)) {
							if (((y + i) >= lower_y) && ((y + i) <= upper_y)) {
								return 1;
							}
						}
					}
				}
			}
		} else {
			for (i = 0; i <= -dy; i++) {
				if (dx > 0) {
					for (j = 0; j <= dx; j++) {
						if (((x + j) >= lower_x) && ((x + j) <= upper_x)) {
							if (((y - i) >= lower_y) && ((y - i) <= upper_y)) {
								return 1;
							}
						}
					}
				} else {
					for (j = 0; j <= -dx; j++) {
						if (((x - j) >= lower_x) && ((x - j) <= upper_x)) {
							if (((y - i) >= lower_y) && ((y - i) <= upper_y)) {
								return 1;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

int BulletEnemyColision(Projectile bullet, Enemy *enemies[]) {
	int i, j, k;
	int lower_x, lower_y, upper_x, upper_y;
	int x = (int) bullet.BulletXpos;
	int y = (int) bullet.BulletYpos;
	double dx = bullet.BulletXSpeed;
	double dy = bullet.BulletYSpeed;
	for (k = 0; k < 20; k++) {
		if (enemies[k] != NULL) {
			lower_x = enemies[k]->x - 3;
			lower_y = enemies[k]->y - 2;
			upper_x = enemies[k]->x + 3;
			upper_y = enemies[k]->y + 3;
			if (dy > 0) {
				for (i = 0; i <= dy; i++) {
					if (dx > 0) {
						for (j = 0; j <= dx; j++) {
							if (((x + j) >= lower_x) && ((x + j) <= upper_x)) {
								if (((y + i) >= lower_y)
										&& ((y + i) <= upper_y)) {
									return k + 1;
								}
							}
						}
					} else {
						for (j = 0; j <= -dx; j++) {
							if (((x - j) >= lower_x) && ((x - j) <= upper_x)) {
								if (((y + i) >= lower_y)
										&& ((y + i) <= upper_y)) {
									return k + 1;
								}
							}
						}
					}
				}
			} else {
				for (i = 0; i <= -dy; i++) {
					if (dx > 0) {
						for (j = 0; j <= dx; j++) {
							if (((x + j) >= lower_x) && ((x + j) <= upper_x)) {
								if (((y - i) >= lower_y)
										&& ((y - i) <= upper_y)) {
									return k + 1;
								}
							}
						}
					} else {
						for (j = 0; j <= -dx; j++) {
							if (((x - j) >= lower_x) && ((x - j) <= upper_x)) {
								if (((y - i) >= lower_y)
										&& ((y - i) <= upper_y)) {
									return k + 1;
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

