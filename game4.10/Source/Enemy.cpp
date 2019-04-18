#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Box.h"
#include "Enemy.h"

game_framework::Enemy::Enemy()
{
	x = 520;
	y = 240;
	bullet = 0;
	Height = 491;
	Width = 491;
	facingX = 0;
	facingY = 0;
	showMagnification = (float)0.12;
	direction = 0;
}

void game_framework::Enemy::LoadBitMap()
{
	bmp[0].LoadBitmap(IDB_ENEMY1, RGB(0, 0, 0));
}

void game_framework::Enemy::OnShow()
{
	if (is_alive)
	{
		bmp[direction].SetTopLeft(x + dx, y + dy);
		bmp[direction].ShowBitmap(showMagnification);
	}

}

void game_framework::Enemy::GetDamage(int damage)
{
	HP -= damage;
}
