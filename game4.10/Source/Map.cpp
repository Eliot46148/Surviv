#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "BasicObject.h"
#include "Map.h"

game_framework::Map::Map()
{
	x = 10;
	y = 10;
	size = 556;
	speed = 10;
	can_breakable = false;
	can_thourghable = true;
	is_alive = true;
	can_move = true;
	isMovingDown = isMovingLeft = isMovingRight = isMovingUp = false;
}

void game_framework::Map::LoadBitMap()
{
	bmp.LoadBitmap(166);
}

void game_framework::Map::OnShow()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			bmp.SetTopLeft(x + size * i, y + size * j);
			bmp.ShowBitmap();
		}
}
