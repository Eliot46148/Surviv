#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Box.h"

game_framework::Box::Box() : BasicObject()
{
    x = 100;
    y = 100;
    Height = 34;
    Width = 34;
    can_thourghable = false;
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

void game_framework::Box::OnShow()
{
    bmp.SetTopLeft(x, y);
    bmp.ShowBitmap(3);
}