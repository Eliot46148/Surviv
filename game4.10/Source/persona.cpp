#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "BasicObject.h"
#include "items.h"
#include "persona.h"

game_framework::persona::persona()
{
    speed = 10;
    HP = 100;
    Height = 556;
    Width = 556;
    x = 290;
    y = 210;
    can_breakable = true;
    can_thourghable = false;
    is_alive = true;
    can_move = true;
    isMovingDown = isMovingLeft = isMovingRight = isMovingUp = false;
}

void game_framework::persona::CatchItem()
{
}

void game_framework::persona::LoadBitMap()
{
    bmp.LoadBitmap(IDB_PLAYER, RGB(0, 0, 0));			// 載入球的圖形
}

void game_framework::persona::OnShow()
{
    if (is_alive)
    {
        bmp.SetTopLeft(x + dx, y + dy);
        bmp.ShowBitmap(0.5);
    }
}

void game_framework::persona::SetGetting(bool flag)
{
	is_Gettting = flag;
}

bool game_framework::persona::isGetting()
{
	return is_Gettting;
}
