#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "BasicObject.h"
#include "shotBullet.h"

game_framework::shotBullet::shotBullet():BasicObject()
{
	LoadBitMap();
	Height = 20;
	Width = 20;
	speed = DEFAULT_BULLET_SPEED;
}

game_framework::shotBullet::shotBullet(int x, int y)
{
	LoadBitMap();
	Height = 20;
	Width = 20;
	speed = DEFAULT_BULLET_SPEED;
	this->x = 320+x;
	this->y = 240+y;
	dx = 2 * x;
	dy = 2 * y;
}

void game_framework::shotBullet::OnMove()
{	
	x += dx;
	y += dy;
}


void game_framework::shotBullet::LoadBitMap()
{
	bmp.LoadBitmap(IDB_BALL, RGB(0, 0, 0));
}

