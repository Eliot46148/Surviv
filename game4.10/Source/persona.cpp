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
    x = SIZE_X / 2 - 75;
    y = SIZE_Y / 2 - 75;
    bullet = 0;
    Height = 128;
    Width = 128;
    facingX = 0;
    facingY = 0;
    showMagnification = (float)0.5;
    direction = 0;
	HP = 100;
	recoil_timer = 0;
	reload_timer = 0;
	holdingItem = 2;
	speed = DEFAULT_CHACRATER_SPEED;
	megazine = 0;
	is_Reloading = false;

}

void game_framework::persona::CatchItem(items take)
{
    if (getHasitemNum() < 2)
    {
        hasitem.push_back(take);
        holdingItem = hasitem.size() - 1;
        hasitemID[hasitem.size() - 1] = hasitem.back().getID();
    }
    else
    {
        hasitem.at(holdingItem) = take;
        hasitemID[holdingItem] = take.getID();
    }
}

bool game_framework::persona::HitObstacle(Box* box, int _where)
{
    int Ox1 = box->GetX(), Oy1 = box->GetY();
    int Ox2 = Ox1 + box->GetWidth(), Oy2 = Oy1 + box->GetHeight();
    int Px1 = x + 45, Py1 = y + 45;
    int Px2 = Px1 + 60, Py2 = Py1 + 60;

    switch (_where)
    {
        case 1:
            Py2 -= 10;
            Py1 -= 10;
            break;

        case 2:
            Py2 += 10;
            Py1 += 10;
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
    bool tem = (Ox2 >= Px1 && Ox1 <= Px2 && Oy2 >= Py1 && Oy1 <= Py2);
    return tem;
}

void game_framework::persona::LoadBitMap()
{
    bmp[0][0].LoadBitmap(IDB_PLAYER1, RGB(0, 0, 0));
    bmp[0][1].LoadBitmap(IDB_PLAYER2, RGB(0, 0, 0));
    bmp[0][2].LoadBitmap(IDB_PLAYER3, RGB(0, 0, 0));
    bmp[0][3].LoadBitmap(IDB_PLAYER4, RGB(0, 0, 0));
    bmp[0][4].LoadBitmap(IDB_PLAYER5, RGB(0, 0, 0));
    bmp[0][5].LoadBitmap(IDB_PLAYER6, RGB(0, 0, 0));
    bmp[0][6].LoadBitmap(IDB_PLAYER7, RGB(0, 0, 0));
    bmp[0][7].LoadBitmap(IDB_PLAYER8, RGB(0, 0, 0));
    bmp[0][8].LoadBitmap(IDB_PLAYER9, RGB(0, 0, 0));
    bmp[0][9].LoadBitmap(IDB_PLAYER10, RGB(0, 0, 0));
    bmp[0][10].LoadBitmap(IDB_PLAYER11, RGB(0, 0, 0));
    bmp[0][11].LoadBitmap(IDB_PLAYER12, RGB(0, 0, 0));
    bmp[0][12].LoadBitmap(IDB_PLAYER13, RGB(0, 0, 0));
    bmp[0][13].LoadBitmap(IDB_PLAYER14, RGB(0, 0, 0));
    bmp[0][14].LoadBitmap(IDB_PLAYER15, RGB(0, 0, 0));
    bmp[0][15].LoadBitmap(IDB_PLAYER16, RGB(0, 0, 0));
    bmp[0][16].LoadBitmap(IDB_PLAYER17, RGB(0, 0, 0));
    bmp[0][17].LoadBitmap(IDB_PLAYER18, RGB(0, 0, 0));
    bmp[0][18].LoadBitmap(IDB_PLAYER19, RGB(0, 0, 0));
    bmp[0][19].LoadBitmap(IDB_PLAYER20, RGB(0, 0, 0));
    bmp[0][20].LoadBitmap(IDB_PLAYER21, RGB(0, 0, 0));
    bmp[0][21].LoadBitmap(IDB_PLAYER22, RGB(0, 0, 0));
    bmp[0][22].LoadBitmap(IDB_PLAYER23, RGB(0, 0, 0));
    bmp[0][23].LoadBitmap(IDB_PLAYER24, RGB(0, 0, 0));
    bmp[1][0].LoadBitmap(IDB_PLAYER_PISTOL1, RGB(0, 0, 0));
    bmp[1][1].LoadBitmap(IDB_PLAYER_PISTOL2, RGB(0, 0, 0));
    bmp[1][2].LoadBitmap(IDB_PLAYER_PISTOL3, RGB(0, 0, 0));
    bmp[1][3].LoadBitmap(IDB_PLAYER_PISTOL4, RGB(0, 0, 0));
    bmp[1][4].LoadBitmap(IDB_PLAYER_PISTOL5, RGB(0, 0, 0));
    bmp[1][5].LoadBitmap(IDB_PLAYER_PISTOL6, RGB(0, 0, 0));
    bmp[1][6].LoadBitmap(IDB_PLAYER_PISTOL7, RGB(0, 0, 0));
    bmp[1][7].LoadBitmap(IDB_PLAYER_PISTOL8, RGB(0, 0, 0));
    bmp[1][8].LoadBitmap(IDB_PLAYER_PISTOL9, RGB(0, 0, 0));
    bmp[1][9].LoadBitmap(IDB_PLAYER_PISTOL10, RGB(0, 0, 0));
    bmp[1][10].LoadBitmap(IDB_PLAYER_PISTOL11, RGB(0, 0, 0));
    bmp[1][11].LoadBitmap(IDB_PLAYER_PISTOL12, RGB(0, 0, 0));
    bmp[1][12].LoadBitmap(IDB_PLAYER_PISTOL13, RGB(0, 0, 0));
    bmp[1][13].LoadBitmap(IDB_PLAYER_PISTOL14, RGB(0, 0, 0));
    bmp[1][14].LoadBitmap(IDB_PLAYER_PISTOL15, RGB(0, 0, 0));
    bmp[1][15].LoadBitmap(IDB_PLAYER_PISTOL16, RGB(0, 0, 0));
    bmp[1][16].LoadBitmap(IDB_PLAYER_PISTOL17, RGB(0, 0, 0));
    bmp[1][17].LoadBitmap(IDB_PLAYER_PISTOL18, RGB(0, 0, 0));
    bmp[1][18].LoadBitmap(IDB_PLAYER_PISTOL19, RGB(0, 0, 0));
    bmp[1][19].LoadBitmap(IDB_PLAYER_PISTOL20, RGB(0, 0, 0));
    bmp[1][20].LoadBitmap(IDB_PLAYER_PISTOL21, RGB(0, 0, 0));
    bmp[1][21].LoadBitmap(IDB_PLAYER_PISTOL22, RGB(0, 0, 0));
    bmp[1][22].LoadBitmap(IDB_PLAYER_PISTOL23, RGB(0, 0, 0));
    bmp[1][23].LoadBitmap(IDB_PLAYER_PISTOL24, RGB(0, 0, 0));
    bmp[2][0].LoadBitmap(IDB_PLAYER_MACHINEGUN1, RGB(0, 0, 0));
    bmp[2][1].LoadBitmap(IDB_PLAYER_MACHINEGUN2, RGB(0, 0, 0));
    bmp[2][2].LoadBitmap(IDB_PLAYER_MACHINEGUN3, RGB(0, 0, 0));
    bmp[2][3].LoadBitmap(IDB_PLAYER_MACHINEGUN4, RGB(0, 0, 0));
    bmp[2][4].LoadBitmap(IDB_PLAYER_MACHINEGUN5, RGB(0, 0, 0));
    bmp[2][5].LoadBitmap(IDB_PLAYER_MACHINEGUN6, RGB(0, 0, 0));
    bmp[2][6].LoadBitmap(IDB_PLAYER_MACHINEGUN7, RGB(0, 0, 0));
    bmp[2][7].LoadBitmap(IDB_PLAYER_MACHINEGUN8, RGB(0, 0, 0));
    bmp[2][8].LoadBitmap(IDB_PLAYER_MACHINEGUN9, RGB(0, 0, 0));
    bmp[2][9].LoadBitmap(IDB_PLAYER_MACHINEGUN10, RGB(0, 0, 0));
    bmp[2][10].LoadBitmap(IDB_PLAYER_MACHINEGUN11, RGB(0, 0, 0));
    bmp[2][11].LoadBitmap(IDB_PLAYER_MACHINEGUN12, RGB(0, 0, 0));
    bmp[2][12].LoadBitmap(IDB_PLAYER_MACHINEGUN13, RGB(0, 0, 0));
    bmp[2][13].LoadBitmap(IDB_PLAYER_MACHINEGUN14, RGB(0, 0, 0));
    bmp[2][14].LoadBitmap(IDB_PLAYER_MACHINEGUN15, RGB(0, 0, 0));
    bmp[2][15].LoadBitmap(IDB_PLAYER_MACHINEGUN16, RGB(0, 0, 0));
    bmp[2][16].LoadBitmap(IDB_PLAYER_MACHINEGUN17, RGB(0, 0, 0));
    bmp[2][17].LoadBitmap(IDB_PLAYER_MACHINEGUN18, RGB(0, 0, 0));
    bmp[2][18].LoadBitmap(IDB_PLAYER_MACHINEGUN19, RGB(0, 0, 0));
    bmp[2][19].LoadBitmap(IDB_PLAYER_MACHINEGUN20, RGB(0, 0, 0));
    bmp[2][20].LoadBitmap(IDB_PLAYER_MACHINEGUN21, RGB(0, 0, 0));
    bmp[2][21].LoadBitmap(IDB_PLAYER_MACHINEGUN22, RGB(0, 0, 0));
    bmp[2][22].LoadBitmap(IDB_PLAYER_MACHINEGUN23, RGB(0, 0, 0));
    bmp[2][23].LoadBitmap(IDB_PLAYER_MACHINEGUN24, RGB(0, 0, 0));
    bmp[3][0].LoadBitmap(IDB_PLAYER_SHOTGUN1, RGB(0, 0, 0));
    bmp[3][1].LoadBitmap(IDB_PLAYER_SHOTGUN2, RGB(0, 0, 0));
    bmp[3][2].LoadBitmap(IDB_PLAYER_SHOTGUN3, RGB(0, 0, 0));
    bmp[3][3].LoadBitmap(IDB_PLAYER_SHOTGUN4, RGB(0, 0, 0));
    bmp[3][4].LoadBitmap(IDB_PLAYER_SHOTGUN5, RGB(0, 0, 0));
    bmp[3][5].LoadBitmap(IDB_PLAYER_SHOTGUN6, RGB(0, 0, 0));
    bmp[3][6].LoadBitmap(IDB_PLAYER_SHOTGUN7, RGB(0, 0, 0));
    bmp[3][7].LoadBitmap(IDB_PLAYER_SHOTGUN8, RGB(0, 0, 0));
    bmp[3][8].LoadBitmap(IDB_PLAYER_SHOTGUN9, RGB(0, 0, 0));
    bmp[3][9].LoadBitmap(IDB_PLAYER_SHOTGUN10, RGB(0, 0, 0));
    bmp[3][10].LoadBitmap(IDB_PLAYER_SHOTGUN11, RGB(0, 0, 0));
    bmp[3][11].LoadBitmap(IDB_PLAYER_SHOTGUN12, RGB(0, 0, 0));
    bmp[3][12].LoadBitmap(IDB_PLAYER_SHOTGUN13, RGB(0, 0, 0));
    bmp[3][13].LoadBitmap(IDB_PLAYER_SHOTGUN14, RGB(0, 0, 0));
    bmp[3][14].LoadBitmap(IDB_PLAYER_SHOTGUN15, RGB(0, 0, 0));
    bmp[3][15].LoadBitmap(IDB_PLAYER_SHOTGUN16, RGB(0, 0, 0));
    bmp[3][16].LoadBitmap(IDB_PLAYER_SHOTGUN17, RGB(0, 0, 0));
    bmp[3][17].LoadBitmap(IDB_PLAYER_SHOTGUN18, RGB(0, 0, 0));
    bmp[3][18].LoadBitmap(IDB_PLAYER_SHOTGUN19, RGB(0, 0, 0));
    bmp[3][19].LoadBitmap(IDB_PLAYER_SHOTGUN20, RGB(0, 0, 0));
    bmp[3][20].LoadBitmap(IDB_PLAYER_SHOTGUN21, RGB(0, 0, 0));
    bmp[3][21].LoadBitmap(IDB_PLAYER_SHOTGUN22, RGB(0, 0, 0));
    bmp[3][22].LoadBitmap(IDB_PLAYER_SHOTGUN23, RGB(0, 0, 0));
    bmp[3][23].LoadBitmap(IDB_PLAYER_SHOTGUN24, RGB(0, 0, 0));
}

void game_framework::persona::OnShow()
{
    if (is_alive)
    {
        const int ID = getHoldingItemID();
        bmp[ID][direction].SetTopLeft(x + camera_x, y + camera_y);
        bmp[ID][direction].ShowBitmap(showMagnification);
    }
}

void game_framework::persona::OnMove()
{	
	int temp;
    if (recoil_timer < 100)
        recoil_timer++;

	if (is_Reloading) {
		reload_timer++;
		if (reload_timer >= 30) {
			reload_timer = 0;
			is_Reloading = false;
			temp = 30 - megazine;
			if (bullet >= temp) {
				bullet -= temp;
				megazine += temp;
			}
			else {
				megazine += bullet;
				bullet = 0;
			}
		}
	}

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

    if (HP > 100)
        HP = 100;
}

void game_framework::persona::Retry()
{
    x = SIZE_X / 2 - 75;
    y = SIZE_Y / 2 - 75;
    bullet = 0;
    Height = 128;
    Width = 128;
    facingX = 0;
    facingY = 0;
    showMagnification = (float)0.5;
    direction = 0;
    HP = 100;
    recoil_timer = 0;
    holdingItem = 2;
    speed = DEFAULT_CHACRATER_SPEED;
    isMovingDown = isMovingLeft = isMovingRight = isMovingUp = false;
}


int game_framework::persona::GetHP()
{
    return HP;
}

int game_framework::persona::GetAmmo()
{
    return bullet;
}

bool game_framework::persona::Recoil()
{
    int ID = getHoldingItemID();
    int Recoil_time;

    switch (ID)
    {
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

    if (recoil_timer > Recoil_time)
    {
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
	if (flag) {
		if (!is_Reloading) {
			is_Reloading = flag;
			reload_timer = 0;
		}
	}
	else
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

	if (bullet > 90)
		bullet = 90;
}

void game_framework::persona::setMegazine(int num)
{
	megazine += num;

}

void game_framework::persona::setFacingPosition(double x, double y)
{
    facingX = x ;
    facingY = y ;
}

void game_framework::persona::setDirection()
{
    if (facingX > 0 && facingY < 0)
    {
        if (facingX < 1.3)
            direction = 0;
        else if (facingX < 3.62)
            direction = 1;
        else if (facingX < 6.08)
            direction = 2;
        else if (facingX < 7.93)
            direction = 3;
        else if (facingX < 9.23)
            direction = 4;
        else if (facingX < 9.91)
            direction = 5;
        else
            direction = 6;
    }

    if (facingX > 0 && facingY > 0)
    {
        if (facingX > 9.91)
            direction = 6;
        else if (facingX > 9.23)
            direction = 7;
        else if (facingX > 7.93)
            direction = 8;
        else if (facingX > 6.08)
            direction = 9;
        else if (facingX > 3.62)
            direction = 10;
        else if (facingX > 1.3)
            direction = 11;
        else
            direction = 12;
    }

    if (facingX < 0 && facingY > 0)
    {
        if (-facingX < 1.3)
            direction = 12;
        else if (-facingX < 3.62)
            direction = 13;
        else if (-facingX < 6.08)
            direction = 14;
        else if (-facingX < 7.93)
            direction = 15;
        else if (-facingX < 9.23)
            direction = 16;
        else if (-facingX < 9.91)
            direction = 17;
        else
            direction = 18;
    }

    if (facingX < 0 && facingY < 0)
    {
        if (-facingX > 9.91)
            direction = 18;
        else if (-facingX > 9.23)
            direction = 19;
        else if (-facingX > 7.93)
            direction = 20;
        else if (-facingX > 6.08)
            direction = 21;
        else if (-facingX > 3.62)
            direction = 22;
        else if (-facingX > 1.3)
            direction = 23;
        else
            direction = 0;
    }
}

void game_framework::persona::setActing(bool flag)
{
    is_acting = flag;
}

void game_framework::persona::getDemage(int damage)
{
    HP -= damage;
}

void game_framework::persona::setHoldingItem(int num)
{
    holdingItem = num;
	int Id = getHoldingItemID();
	switch (Id) {
	case 1:
		reload_timer = 30;
		break;
	case 2:
		reload_timer = 50;
		break;
	case 3:
		reload_timer = 75;
		break;
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

int game_framework::persona::GetHitpointX()
{
    return x + 75;
}

int game_framework::persona::GetHitpointY()
{
    return y + 75;
}



int game_framework::persona::getHasitemNum()
{
    return (int)hasitem.size();
}

int* game_framework::persona::GetHasItemID()
{
    return hasitemID;
}

int game_framework::persona::GetHoldingItem()
{
    return holdingItem;
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

int game_framework::persona::GetMegazine()
{
	return megazine;
}
