#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "BasicObject.h"


namespace game_framework {
	BasicObject::BasicObject()
	{
		x = 0;
		y = 0;
		dx = 0;
		dy = 0;
		Height = 556;
		Width = 556;
		HP = 10;
		speed = DEFAULT_OBJECTIVE_SPEED;
		can_breakable = false;
		can_thourghable = true;
		is_alive = true;
		can_move = true;
		isMovingDown = isMovingLeft = isMovingRight = isMovingUp = false;
	}
	void BasicObject::OnMove()
{
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
void BasicObject::OnShow()
{
    if (is_alive)
    {
        bmp.SetTopLeft(x + dx, y + dy);
        bmp.ShowBitmap();
    }
}
void BasicObject::SetXY(int nx, int ny)
{
    x = nx;
    y = ny;
}
void BasicObject::SetMovingUP(bool flag)
{
    isMovingUp = flag;
}
void BasicObject::SetMovingDown(bool flag)
{
    isMovingDown = flag;
}
void BasicObject::SetMovingLeft(bool flag)
{
    isMovingLeft = flag;
}
void BasicObject::SetMovingRight(bool flag)
{
    isMovingRight = flag;
}
void BasicObject::SetAlive(bool flag)
{
	is_alive = flag;
}
int BasicObject::GetX()
{
	return x;
}
int BasicObject::GetY()
{
	return y;
}
bool BasicObject::isAlive()
{
    return is_alive;
}
bool BasicObject::isThourghable()
{
    return can_thourghable;
}
bool BasicObject::isBreakable()
{
    return can_breakable;
}
}
