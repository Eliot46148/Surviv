#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Texture.h"

game_framework::Texture::Texture(int x, int y, int skinid)
{
    this->x = x;
    this->y = y;
    skin = skinid;
    showMagnification = 3;
    LoadBitMap();
	
}


void game_framework::Texture::LoadBitMap()
{
    switch (skin)
    {
        case 1:
            bmp.LoadBitmap(IDB_BOXBREAK, RGB(0, 0, 0));
            showMagnification = (float)0.6;
            break;
    }
}
