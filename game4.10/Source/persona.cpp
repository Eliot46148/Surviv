#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "BasicObject.h"
#include "items.h"
#include "persona.h"

class items;

game_framework::persona::persona(): BasicObject()
{
    x = 320;
    y = 240;
    bullet = 0;
    Height = 64;
    Width = 64;
    facingX = 0;
    facingY = 0;
    showMagnification = (float)0.5;
	direction = 0;
}

void game_framework::persona::CatchItem(items take)
{
    hasitem.push_back(take);
}

bool game_framework::persona::HitObstacle(Box * box, int _where)
{
	int Ox1 = box->GetX(), Oy1 = box->GetY();
	int Ox2 = box->GetX() + box->GetWidth(), Oy2 = box->GetY() + box->GetHeight();
	int Px1 = x, Py1 = y, Px2 = x + (int)(Width * showMagnification), Py2 = y + (int)(Height * showMagnification);
	switch (_where)
	{
	case 1:
		Py2 -= 10;
		Py1 -= 10;
		break;
	case 2:
		Py2 += 10;
		Py1 -= 10;
		break;
	case 3:
		Px2 -= 10;
		Px1 -= 10;
		break;	
	case 4:
		Px2 += 10;
		Px1 += 10;
		break;
	}
	//return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
	return (Ox2 >= Px1 && Ox1 <= Px2 && Oy2 >= Py1 && Oy1 <= Py2);

}

void game_framework::persona::LoadBitMap()
{
	bmp[0].LoadBitmap(IDB_PLAYER1, RGB(0, 0, 0));
	bmp[1].LoadBitmap(IDB_PLAYER2, RGB(0, 0, 0));
	bmp[2].LoadBitmap(IDB_PLAYER3, RGB(0, 0, 0));
	bmp[3].LoadBitmap(IDB_PLAYER4, RGB(0, 0, 0));
	bmp[4].LoadBitmap(IDB_PLAYER5, RGB(0, 0, 0));
	bmp[5].LoadBitmap(IDB_PLAYER6, RGB(0, 0, 0));
	bmp[6].LoadBitmap(IDB_PLAYER7, RGB(0, 0, 0));
	bmp[7].LoadBitmap(IDB_PLAYER8, RGB(0, 0, 0));
}

void game_framework::persona::OnShow()
{
    if (is_alive)
    {	
        bmp[direction].SetTopLeft(x + dx, y + dy);
        bmp[direction].ShowBitmap(0.5);
    }
}

void game_framework::persona::returnBlood()
{
	HP += 10;
}

int game_framework::persona::ShowHP()
{
	return HP;
}

void game_framework::persona::SetGetting(bool flag)
{
    is_Gettting = flag;
}

void game_framework::persona::SetReloading(bool flag)
{
    is_Reloading = flag;
}

bool game_framework::persona::isGetting()
{
    return is_Gettting;
}


bool game_framework::persona::isReloading()
{
    return is_Reloading;
}

bool game_framework::persona::isCan_Right()
{
    return isMovingRight;
}

bool game_framework::persona::isCan_Left()
{
    return isMovingLeft;
}

bool game_framework::persona::isCan_Down()
{
    return isMovingUp;
}

bool game_framework::persona::isCan_UP()
{
    return isMovingUp;
}

void game_framework::persona::setCan_move(bool flag)
{
    can_move = flag;
}

void game_framework::persona::setBullet(int num)
{
    bullet += num;
}

void game_framework::persona::setFacingPosition(double x, double y)
{
    facingX = x;
    facingY = y;
}

void game_framework::persona::setDirection()
{
	if (facingX > 0 && facingY < 0) {
		if (facingX < 3.8)
			direction = 0;
		else if (facingX < 9.23)
			direction = 1;
		else
			direction = 2;
	}
	if (facingX > 0 && facingY > 0) {
		if (facingX > 9.23)
			direction = 2;
		else if (facingX > 3.8)
			direction = 3;
		else
			direction = 4;
	}
	if (facingX < 0 && facingY > 0) {
		if (facingX <-9.23)
			direction = 6;
		else if (facingX<-3.8)
			direction = 5;
		else
			direction = 4;
	}
	if (facingX < 0 && facingY < 0) {
		if (facingX < -9.23)
			direction = 6;
		else if (facingX<-3.8)
			direction = 7;
		else
			direction = 0;
	}

}

double game_framework::persona::getFacingX()
{
    return facingX;
}

double game_framework::persona::getFacingY()
{
    return facingY;
}

int game_framework::persona::getHasitemNum()
{
    return (int)hasitem.size();
}

int game_framework::persona::getBullet()
{
    return bullet;
}



