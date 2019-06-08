#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "BasicObject.h"
#include "Blood.h"

game_framework::Blood::Blood(): BasicObject()
{
    LoadBitMap();
}

void game_framework::Blood::OnMove()
{
    if(!is_Dead)
        timer++;

    if (timer > survival_time)
        is_Dead = true;
}

void game_framework::Blood::LoadBitMap()
{
    bmp.LoadBitmap(IDB_BLOOD, RGB(255, 255, 255));
    timer = 0;
    is_Dead = false;
}

bool game_framework::Blood::IsDead()
{
    return is_Dead;
}
