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
	Height = 33;
	Width = 34;
	can_thourghable = false;
}

void game_framework::Box::LoadBitMap()
{
	bmp.LoadBitmap(167);
}

void game_framework::Box::OnShow()
{
	for (int i=0;i<3;i++)
		for (int j = 0; j < 3; j++) {
			bmp.SetTopLeft(x + i * 100, y + j * 100);
			bmp.ShowBitmap();
		}
}


