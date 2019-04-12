#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "BasicObject.h"
#include "shotBullet.h"

game_framework::shotBullet::shotBullet(): BasicObject()
{
    LoadBitMap();
    Height = 20;
    Width = 20;
	damage = 10;
    speed = DEFAULT_BULLET_SPEED;
}

game_framework::shotBullet::shotBullet(int x, int y)
{
    LoadBitMap();
    Height = 20;
    Width = 20;
    speed = DEFAULT_BULLET_SPEED;
    this->x = 320 + x;
    this->y = 240 + y;
    dx = 2 * x;
    dy = 2 * y;
}

void game_framework::shotBullet::OnMove()
{
    x += dx;
    y += dy;

    if (isMovingLeft)
        x -= speed;

    if (isMovingRight)
        x += speed;

    if (isMovingUp)
        y -= speed;

    if (isMovingDown)
        y += speed;
}


void game_framework::shotBullet::LoadBitMap()
{
    bmp.LoadBitmap(IDB_BALL, RGB(0, 0, 0));
}

bool game_framework::shotBullet::HitPlayer(persona* player)
{
    int px1 = player->GetX(), py1 = player->GetY();
    int px2 = player->GetX() + player->GetWidth(), py2 = player->GetY() + player->GetHeight();
    return HitSomething(px1, py1, px2, py2);
}

bool game_framework::shotBullet::HitObstacle(Box* box)
{
    int bx1 = box->GetX(), by1 = box->GetY();
    int bx2 = box->GetX() + box->GetWidth(), by2 = box->GetY() + box->GetHeight();
    return HitSomething(bx1, by1, bx2, by2);
}

bool game_framework::shotBullet::HitSomething(int tx1, int ty1, int tx2, int ty2)
{
    int sx1 = x, sx2 = x + Width, sy1 = y, sy2 = y + Height;
    return (tx2 >= sx1 && tx1 <= sx2 && ty2 >= sy1 && ty1 <= sy2);
}

int game_framework::shotBullet::ShowDamage()
{
	return damage;
}

