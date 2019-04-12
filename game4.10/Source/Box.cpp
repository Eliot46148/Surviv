#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Box.h"

game_framework::Box::Box() : BasicObject()
{
    x = 98;
    y = 98;
    Height = 34;
    Width = 34;
    showMagnification = 3;
}

game_framework::Box::Box(int x, int y): Box()
{
    this->x = x;
    this->y = y;
}

void game_framework::Box::LoadBitMap()
{
    bmp.LoadBitmap(167);
}
