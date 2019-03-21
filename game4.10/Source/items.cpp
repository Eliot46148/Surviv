#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "BasicObject.h"
#include "items.h"

game_framework::items::items()
{
	x = 400;
	y = 400;
}

void game_framework::items::LoadBitMap()
{
	bmp.LoadBitmap(IDB_PISTOL1,RGB(0,0,0));			// 載入球的圖形

}

void game_framework::items::OnShow()
{
	bmp.SetTopLeft(x, y);
	bmp.ShowBitmap(0.4);
}
