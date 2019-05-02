#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "BasicObject.h"
#include "items.h"
#include <vector>
#include "persona.h"

class items;
class Box;

game_framework::persona::persona(): BasicObject()
{
    x = 320;
    y = 240;
    bullet = 0;
    Height = 128;
    Width = 128;
    facingX = 0;
    facingY = 0;
    showMagnification = (float)0.5;
    direction = 0;
	recoil_timer = 0;
	holdingItem = 2;
	speed = DEFAULT_OBJECTIVE_SPEED;
}

void game_framework::persona::CatchItem(items take)
{
    hasitem.push_back(take);
	holdingItem = hasitem.size() - 1;
}

bool game_framework::persona::HitObstacle(Box* box, int _where)
{
    int Ox1 = box->GetX(), Oy1 = box->GetY();
    int Ox2 = Ox1 + box->GetWidth(), Oy2 = Oy1 + box->GetHeight();
    int Px1 = x, Py1 = y;
    int Px2 = Px1 + (int)(Width * showMagnification), Py2 = Py1 + (int)(Height * showMagnification);

	switch (_where)
    {
        case 1:
            Oy2 -= 10;
            Oy1 -= 10;
            break;

        case 2:
		    Oy2 += 10;
            Oy1 += 10;
            break;

        case 3:
            Ox2 -= 10;
            Ox1 -= 10;
            break;

        case 4:
            Ox2 += 10;
            Ox1 += 10;
            break;
    }
	
    //return (tx2 >= x1 && tx1 <= x2 && ty2 >= y1 && ty1 <= y2);
    bool tem = (Ox2 >= Px1 && Ox1 <= Px2 && Oy2 >= Py1 && Oy1 <= Py2);
    return tem;
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
        bmp[direction].SetTopLeft(SIZE_X/2, SIZE_Y/2);
        bmp[direction].ShowBitmap(showMagnification);
    }
}

void game_framework::persona::OnMove()
{
	if (recoil_timer < 100)
		recoil_timer++;

	if (!(can_move && is_alive))
		return;

	if (isMovingLeft)
		x -= speed;

	if (isMovingRight)
		x += speed;

	if (isMovingUp)
		y -= speed;

	if (isMovingDown)
		y += speed;
}

void game_framework::persona::returnBlood()
{
    HP += 10;
}

int game_framework::persona::ShowHP()
{
    return HP;
}

bool game_framework::persona::Recoil()
{	
	int ID = getHoldingItemID();
	int Recoil_time;
	switch (ID) {
		case 1:
			Recoil_time = 20;
			break;
		case 2:
			Recoil_time = 5;
			break;
		case 3:
			Recoil_time = 30;
			break;
		default:
			Recoil_time = 100;
	}
	if (recoil_timer > Recoil_time) {
		recoil_timer = 0;
		return false;
	}
	else
		return true;
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

bool game_framework::persona::isActing()
{
	return is_acting;
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
    if (facingX > 0 && facingY < 0)
    {
        if (facingX < 3.8)
            direction = 0;
        else if (facingX < 9.23)
            direction = 1;
        else
            direction = 2;
    }

    if (facingX > 0 && facingY > 0)
    {
        if (facingX > 9.23)
            direction = 2;
        else if (facingX > 3.8)
            direction = 3;
        else
            direction = 4;
    }

    if (facingX < 0 && facingY > 0)
    {
        if (facingX < -9.23)
            direction = 6;
        else if (facingX < -3.8)
            direction = 5;
        else
            direction = 4;
    }

    if (facingX < 0 && facingY < 0)
    {
        if (facingX < -9.23)
            direction = 6;
        else if (facingX < -3.8)
            direction = 7;
        else
            direction = 0;
    }
}

void game_framework::persona::setActing(bool flag)
{
	is_acting = flag;
}

void game_framework::persona::setHoldingItem(int num)
{
	holdingItem = num;
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

int game_framework::persona::getHoldingItemID()
{
	if (holdingItem == 2)
		return 0;
	else
		return hasitem.at(holdingItem).getID();
}

int game_framework::persona::getBullet()
{
    return bullet;
}