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

void game_framework::Enemy::GetDamage(int damage)
{
    HP -= damage;
}

void game_framework::Enemy::SetNearBox(Box* nbox)
{
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
        movevector = rand() % 8 + 1;
        moveDelay = 45;
    }

	random = 3;

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

void game_framework::Enemy::attackNearPeople()
{
    movevector = rand() % static_cast<int>(nearPerson.size()) + 1;
    /*if (player1.isActing())
    {
    	if (!player1.isReloading() && !player1.Recoil() && player1.getBullet() > 0)
    	{
    		int ID = player1.getHoldingItemID();
    		int x = (int)player1.getFacingX(), y = (int)player1.getFacingY();

    		switch (ID)
    		{
    		case 1:
    		case 2:
    			shotbullets.push_back(shotBullet((int)player1.getFacingX(), (int)player1.getFacingY()));
    			break;

    		case 3:
    			int degree = 10, temp = degree;
    			shotbullets.push_back(shotBullet((int)player1.getFacingX(), (int)player1.getFacingY()));
    			shotbullets.push_back(shotBullet(int(x * cos(temp * M_PI / 180) - y * sin(temp * M_PI / 180)), int(x * sin(temp * M_PI / 180) + y * cos(temp * M_PI / 180))));
    			temp = degree * 2;
    			shotbullets.push_back(shotBullet(int(x * cos(temp * M_PI / 180) - y * sin(temp * M_PI / 180)), int(x * sin(temp * M_PI / 180) + y * cos(temp * M_PI / 180))));
    			temp = degree * -1;
    			shotbullets.push_back(shotBullet(int(x * cos(temp * M_PI / 180) - y * sin(temp * M_PI / 180)), int(x * sin(temp * M_PI / 180) + y * cos(temp * M_PI / 180))));
    			temp = degree * -2;
    			shotbullets.push_back(shotBullet(int(x * cos(temp * M_PI / 180) - y * sin(temp * M_PI / 180)), int(x * sin(temp * M_PI / 180) + y * cos(temp * M_PI / 180))));
    			break;
    		}
    	}
    }*/
}

void game_framework::Enemy::getNearItems()
{
	int  a = nearitems.at(0)->GetWidth();
	int b = this->GetWidth();
   /* if ((nearitems.at(0)->GetX() + nearitems.at(0)->GetWidth()) / 2 < (this->x + this->GetWidth()) / 2)
        isMovingLeft = 1;
    else if ((nearitems.at(0)->GetX() + nearitems.at(0)->GetWidth()) / 2 > (this->x + this->GetWidth()) / 2)
        isMovingRight = 1;

    if ((nearitems.at(0)->GetY() + nearitems.at(0)->GetHeight()) / 2 < (this->y + this->GetHeight()) / 2)
        isMovingUp = 1;
    else if ((nearitems.at(0)->GetY() + nearitems.at(0)->GetHeight()) / 2 > (this->y + this->GetHeight()) / 2)
        isMovingDown = 1;
		*/
	 if (nearitems.at(0)->GetX()<this->x+10)
		 isMovingLeft = 1;
	 else if (nearitems.at(0)->GetX()>this->x+10 )
		 isMovingRight = 1;

	 if (nearitems.at(0)->GetY()<this->y+10)
		 isMovingUp = 1;
	 else if (nearitems.at(0)->GetY()>this->y+10)
		 isMovingDown = 1;

    moveDelay = 2;
}

void game_framework::Enemy::getNeatBullet()
{
    if (nearBuller.at(0)->GetX() < this->x+10)
        isMovingLeft = 1;
    else if (nearBuller.at(0)->GetX() > this->x+10)
        isMovingRight = 1;

    if (nearBuller.at(0)->GetY() < this->y+10)
        isMovingUp = 1;
    else if (nearBuller.at(0)->GetY() > this->y+10)
        isMovingDown = 1;

    moveDelay = 2;
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

void game_framework::Enemy::Catchbullt(int bu)
{
    bullet += bu;
    moveDelay = 0;
}

void game_framework::Enemy::CatchItom(items it)
{
    hasitem.push_back(it);
    moveDelay = 0;
}

int game_framework::Enemy::hasItom()
{
	return hasitem.size();
}

void game_framework::Enemy::setbullt(int num)
{
	bullet += num;
}

int game_framework::Enemy::hasbullt()
{
	return bullet;
}
