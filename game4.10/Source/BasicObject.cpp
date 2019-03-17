#include "stdafx.h"
#include "BasicObject.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

namespace game_framework {
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
