#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Box.h"
#include "Enemy.h"

game_framework::Enemy::Enemy()
{
    x = 520;
    y = 240;
    bullet = 0;
    Height = 114;
    Width = 114;
    showMagnification = (float)0.12;
    direction = 0;
    skin = 1;
    moveDelay = 0;
	speed = 5;
}
game_framework::Enemy::Enemy(int nx, int ny, int skinid)
{
    x = nx;
    y = ny;
    bullet = 0;
    Height = 114;
    Width = 114;
    skin = skinid;
    direction = 0;
    showMagnification = (float)0.5;
    moveDelay = 0;
	speed = 5;

}


void game_framework::Enemy::LoadBitMap()
{
    switch (skin)
    {
        case 1:
            bmp[0].LoadBitmap(IDB_ENEMY1, RGB(0, 0, 0));
            break;

        case 2:
            bmp[0].LoadBitmap(IDB_ENEMY2, RGB(0, 0, 0));
            break;

        case 3:
            bmp[0].LoadBitmap(IDB_ENEMY3, RGB(0, 0, 0));
            break;

        default:
            bmp[0].LoadBitmap(IDB_ENEMY1, RGB(0, 0, 0));
            break;
    }
}

void game_framework::Enemy::OnShow()
{
    if (is_alive)
    {
        bmp[direction].SetTopLeft(x + dx + camera_x, y + dy + camera_y);
        bmp[direction].ShowBitmap(showMagnification);
    }
}

void game_framework::Enemy::GetDamage(int damage)
{
    HP -= damage;
}

void game_framework::Enemy::SetNearBox(Box* nbox)
{
}

void game_framework::Enemy::ClearBBIvector()
{
    nearBox.clear();
    nearBuller.clear();
    nearitems.clear();
}

void game_framework::Enemy::SetNearBullet(Bullet* nbullet)
{
    nearBuller.push_back(nbullet);
}

void game_framework::Enemy::SetNearItem(items* nitem)
{
    nearitems.push_back(nitem);
}

void game_framework::Enemy::chouseMode()
{
    // 移動--1   攻擊--2  剪取--3
    isMovingDown = 0;
    isMovingLeft = 0;
    isMovingRight = 0;
    isMovingUp = 0;

    if (moveDelay == 0)
    {
        random = rand() % (3) + 1;
        movevector = rand() % 10 + 1;
        moveDelay = 45;
    }

	switch (random)
    {
        case 1:
            this->movetoplace();
            break;

        case 2:
            if (static_cast<int>(nearBox.size()) != 0 )
                this->attackNearPeople();
            else
                this->movetoplace();
            break;

        case 3:
            if (static_cast<int>(nearitems.size()) != 0 && static_cast<int>(this->hasitem.size()) < 2)
                this->getNearItems();
            else
                this->movetoplace();
            break;
    }

    moveDelay--;

    if (y <= 0)
        isMovingUp = 0;

    if (y >= 556 * 5)
        isMovingDown = 0;

    if (x <= 0)
        isMovingLeft = 0;

    if (x >= 556 * 5)
        isMovingRight = 0;
}

void game_framework::Enemy::attackNearPeople()
{
	
}

void game_framework::Enemy::getNearItems()
{
	if (nearitems.at(0)->GetX() < this->x)
		isMovingLeft = 1;
	else if (nearitems.at(0)->GetX() > this->x)
		isMovingRight = 1;
	if (nearitems.at(0)->GetY() < this->y)
		isMovingUp = 1;
	else if (nearitems.at(0)->GetY() > this->y)
		isMovingDown = 1;
}

void game_framework::Enemy::movetoplace()
{
	random = 1;
    switch (movevector)
    {
        case 1://上
            isMovingUp = 1;
            break;

        case 2://下
            isMovingDown = 1;
            break;

        case 3://左
            isMovingLeft = 1;
            break;

        case 4://右
            isMovingRight = 1;
            break;

        case 5://右上
            isMovingUp = 1;
            isMovingRight = 1;
            break;

        case 6://左上
            isMovingUp = 1;
            isMovingLeft = 1;
            break;

        case 7://左下
            isMovingLeft = 1;
            isMovingDown = 1;
            break;

        case 8://右下
            isMovingRight = 1;
            isMovingDown = 1;
            break;

        default:
            break;
    }
}
