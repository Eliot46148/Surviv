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
    itemsdamage = 5;
}

game_framework::items::items(int x, int y, int id, float showsize) : BasicObject()
{
    this->x = x;
    this->y = y;
    showMagnification = showsize;
    itemsID = id;
}

void game_framework::items::LoadBitMap()
{
    switch (itemsID)
    {
        case 1:
            bmp.LoadBitmap(IDB_PISTOL1, RGB(0, 0, 0));			// ¤âºj
            break;

        case 2:
            bmp.LoadBitmap(IDB_MachineGun, RGB(0, 0, 0));		// ¾÷ºj
            break;

        case 3:
            bmp.LoadBitmap(IDB_ShotGun, RGB(0, 0, 0));          // ÄÅ¼uºj
            break;

        case 4:
            bmp.LoadBitmap(IDB_Bandage, RGB(0, 0, 0));          // Á^±a
            break;

        default:
            break;
    }
}

int game_framework::items::getID()
{
    return itemsID;
}

