#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Box.h"
#include "shotBullet.h"
#include "persona.h"
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
    HP = 50;
    hasitem.clear();
    ClearBBIPvector();
}

game_framework::Enemy::Enemy(int nx, int ny, int skinid)
{
    x = nx;
    y = ny;
    HP = 50;
    bullet = 0;
    Height = 114;
    Width = 114;
    skin = skinid;
    direction = 0;
    showMagnification = (float)0.5;
    moveDelay = 0;
    speed = 5;
    hasitem.clear();
    ClearBBIPvector();
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

void game_framework::Enemy::OnMove()
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

void game_framework::Enemy::GetDamage(int damage)
{
    HP -= damage;
}

void game_framework::Enemy::SetNearBox(Box* nbox)
{
    nearBox.push_back(nbox);
}

void game_framework::Enemy::ClearBBIPvector()
{
    nearPerson.clear();
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

void game_framework::Enemy::SetCamera(int x, int y)
{
	camera_x = x;
	camera_y = y;
}

void game_framework::Enemy::chouseMode()
{
    // ����--1   ����--2  �Ũ�--3
    isMovingDown = 0;
    isMovingLeft = 0;
    isMovingRight = 0;
    isMovingUp = 0;

    if (moveDelay == 0)
    {
        random = rand() % (2) + 1;
        movevector = rand() % 9 + 1;
        moveDelay = 45;
    }

    if (static_cast<int>(nearPerson.size()) != 0 && static_cast<int>(hasitem.size()) != 0)
        this->is_acting = true;
    else
        this->is_acting = false;

    switch (random)
    {
        case 1:
            this->movetoplace();
            break;

        case 2:
            if (static_cast<int>(nearitems.size()) != 0 && static_cast<int>(this->hasitem.size()) < 2)
                this->getNearItems();
            else if (static_cast<int>(nearBuller.size()) != 0 && this->bullet < 300)
                this->getNeatBullet();
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

int game_framework::Enemy::rtNearPeople()
{
    return static_cast<int>(nearPerson.size());
}

void game_framework::Enemy::getNearItems()
{
    if (nearitems.at(0)->GetX() < this->x + 10)
        isMovingLeft = 1;
    else if (nearitems.at(0)->GetX() > this->x + 10 )
        isMovingRight = 1;

    if (nearitems.at(0)->GetY() < this->y + 10)
        isMovingUp = 1;
    else if (nearitems.at(0)->GetY() > this->y + 10)
        isMovingDown = 1;

    moveDelay = 2;
}

void game_framework::Enemy::getNeatBullet()
{
    if (nearBuller.at(0)->GetX() < this->x + 10)
        isMovingLeft = 1;
    else if (nearBuller.at(0)->GetX() > this->x + 10)
        isMovingRight = 1;

    if (nearBuller.at(0)->GetY() < this->y + 10)
        isMovingUp = 1;
    else if (nearBuller.at(0)->GetY() > this->y + 10)
        isMovingDown = 1;

    moveDelay = 2;
}

void game_framework::Enemy::movetoplace()
{
    random = 1;

    switch (movevector)
    {
        case 1://�W
            isMovingUp = 1;
            break;

        case 2://�U
            isMovingDown = 1;
            break;

        case 3://��
            isMovingLeft = 1;
            break;

        case 4://�k
            isMovingRight = 1;
            break;

        case 5://�k�W
            isMovingUp = 1;
            isMovingRight = 1;
            break;

        case 6://���W
            isMovingUp = 1;
            isMovingLeft = 1;
            break;

        case 7://���U
            isMovingLeft = 1;
            isMovingDown = 1;
            break;

        case 8://�k�U
            isMovingRight = 1;
            isMovingDown = 1;
            break;

        default:
            break;
    }
}

void game_framework::Enemy::Catchbullt(int bu)
{
    bullet += bu;
    moveDelay = 0;
}

void game_framework::Enemy::CatchItem(items it)
{
    hasitem.push_back(it);
    moveDelay = 0;
}

void game_framework::Enemy::setnearperson(persona* ps)
{
    nearPerson.push_back(*ps);
}

int game_framework::Enemy::hasItom()
{
    return hasitem.size();
}

int game_framework::Enemy::rtItom(int no)
{
    return hasitem[no].getID();
}

void game_framework::Enemy::setbullt(int num)
{
    bullet += num;
}

int game_framework::Enemy::sizeitom()
{
    return hasitem.size();
}

int game_framework::Enemy::hasbullet()
{
    return bullet;
}

bool game_framework::Enemy::isActing()
{
    return is_acting;
}

int game_framework::Enemy::catchitemID()
{
    return hasitem.at(0).getID();
}

bool game_framework::Enemy::tutchbox(Box* box, int _where)
{
    int Ox1 = box->GetX(), Oy1 = box->GetY();
    int Ox2 = Ox1 + box->GetWidth(), Oy2 = Oy1 + box->GetHeight();
    int Px1 = x, Py1 = y;
    int Px2 = Px1 + (int)(Width * showMagnification), Py2 = Py1 + (int)(Height * showMagnification);

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

        case 0:
            break;
    }

    bool tem = (Ox2 >= Px1 && Ox1 <= Px2 && Oy2 >= Py1 && Oy1 <= Py2);
    return tem;
}

bool game_framework::Enemy::hitBox(Box* box)
{
    int count = 0;

    if (tutchbox(box, 1))
    {
        count++;
        isMovingDown = 1;
    }

    if (tutchbox(box, 2))
    {
        count++;
        isMovingUp = 1;
    }

    if (tutchbox(box, 3))
    {
        count++;
        isMovingRight = 1;
    }

    if (tutchbox(box, 4))
    {
        count++;
        isMovingLeft = 1;
    }

    if (count != 0)
    {
        is_acting = true;
        return true;
    }

    return false;
}

