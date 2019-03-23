#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "items.h"

game_framework::items::items(): BasicObject()
{
    x = 400;
    y = 400;
}

game_framework::items::items(int x, int y)
{
    this->x = x;
    this->y = y;
}

void game_framework::items::LoadBitMap()
{
    bmp.LoadBitmap(IDB_PISTOL1, RGB(0, 0, 0));			// ºj
}

void game_framework::items::OnShow()
{
    if (isAlive())
    {
        bmp.SetTopLeft(x, y);
        bmp.ShowBitmap(0.4);
    }
}
