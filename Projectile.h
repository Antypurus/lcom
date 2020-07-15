#pragma once

#include "sprite.h"

typedef struct{
	double angle;
	double BulletXpos;
	double BulletYpos;
	SPRITE sprite; //ignorar - nao usado
	char *SpritePath; //ognorar - nao usado
	int BulletSpeed;
	double BulletXSpeed;
	double BulletYSpeed;
	int isVoid; //ignorar - não usado
}Projectile;

typedef struct{
	int x;
	int y;
	int XRange;
	int YRange;
	int Orientation;
}Wall;

typedef struct{
	int x;
	int y;
}Enemy;

Projectile New_Projectile(int MouseXpos,int MouseYpos,int PlayerXpos,int PlayerYpos);

Wall New_Wall();

void DrawWall(Wall *wall);

Enemy New_Enemy();

void DrawEnemy(Enemy *enemy[]);

int BulletWallColision(Projectile bullet,Wall *walls);

int BulletEnemyColision(Projectile bullet,Enemy *enemies[]);

int PlayerWallColision(int PlauerX,int PlayerY,int PlauerXSpeed,int PlauerYSpeed,Wall *walls);


