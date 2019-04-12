#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Bullet.h"

game_framework::Bullet::Bullet()
{
}

game_framework::Bullet::Bullet(int x, int y)
{
    this->x = x;
    this->y = y;
}

void game_framework::Bullet::LoadBitMap()
{
    bmp.LoadBitmap(171);
}
