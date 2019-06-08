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
    ID = 1;
}

game_framework::shotBullet::shotBullet(int x, int y, int position_x, int position_y, int camera_x, int camera_y, int hshout, int ID)
{
    LoadBitMap();
    Height = 20;
    damage = 10;
    Width = 20;
    speed = DEFAULT_BULLET_SPEED;
    this->x = position_x + x;
    this->y = position_y + y;
    this->camera_x = camera_x;
    this->camera_y = camera_y;
    this->ID = ID;
    dx = int(2 * x / 10);
    dy = int(2 * y / 10);
    shooter = hshout;
    LoadBitMap();
}

void game_framework::shotBullet::OnMove()
{
    x += dx;
    y += dy;

    if (isMovingLeft)
        x -= DEFAULT_CHACRATER_SPEED;

    if (isMovingRight)
        x += DEFAULT_CHACRATER_SPEED;

    if (isMovingUp)
        y -= DEFAULT_CHACRATER_SPEED;

    if (isMovingDown)
        y += DEFAULT_CHACRATER_SPEED;
}


void game_framework::shotBullet::LoadBitMap()
{
    if(ID == 1)
        bmp.LoadBitmap(IDB_BALL, RGB(0, 0, 0));
    else if (ID == 2)
        bmp.LoadBitmap(IDB_BALL2, RGB(0, 0, 0));
}

bool game_framework::shotBullet::HitPlayer(persona* player)
{
    int px1 = player->GetHitpointX(), py1 = player->GetHitpointY();
    int px2 = player->GetHitpointX() + player->GetWidth(), py2 = player->GetHitpointY() + player->GetHeight();
    return HitSomething(px1, py1, px2, py2);
}

bool game_framework::shotBullet::HitEnemy(Enemy* enemy)
{
    int px1 = enemy->GetX(), py1 = enemy->GetY();
    int px2 = enemy->GetX() + enemy->GetWidth(), py2 = enemy->GetY() + enemy->GetHeight();
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

int game_framework::shotBullet::getshooter()
{
    return shooter;
}
