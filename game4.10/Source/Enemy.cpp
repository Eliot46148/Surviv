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
    Height = 114;
    Width = 114;
    showMagnification = (float)0.12;
    direction = 0;
    skin = 1;
	moveDelay = 0;
}
game_framework::Enemy::Enemy(int nx, int ny, int skinid)
{
    x = nx;
    y = ny;
    bullet = 0;
    Height = 114;
    Width = 114;
    skin = skinid;
    direction = 0;
    showMagnification = (float)0.5;
	moveDelay = 0;
}


void game_framework::Enemy::LoadBitMap()
{
    switch (skin)
    {
        case 1:
            bmp[0].LoadBitmap(IDB_ENEMY1, RGB(0, 0, 0));
            break;

        case 2:
            bmp[0].LoadBitmap(IDB_ENEMY2, RGB(0, 0, 0));
            break;

        case 3:
            bmp[0].LoadBitmap(IDB_ENEMY3, RGB(0, 0, 0));
            break;

        default:
            bmp[0].LoadBitmap(IDB_ENEMY1, RGB(0, 0, 0));
            break;
    }
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
