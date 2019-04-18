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
    HP = 20;
    speed = DEFAULT_OBJECTIVE_SPEED;
    can_breakable = false;
    is_alive = true;
    can_move = true;
    isMovingDown = isMovingLeft = isMovingRight = isMovingUp = false;
    showMagnification = 1;
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
        bmp.SetTopLeft(x, y);
        bmp.ShowBitmap(showMagnification);
    }
}
void BasicObject::setMovingMode(int path, bool flag)
{
    switch (path)
    {
        case 1:
            isMovingUp = flag;
            break;

        case 2:
            isMovingDown = flag;
            break;

        case 3:
            isMovingLeft = flag;
            break;

        case 4:
            isMovingRight = flag;
            break;

        default:
            break;
    }
}
void BasicObject::SetXY(int nx, int ny)
{
    x = nx;
    y = ny;
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
int BasicObject::GetHeight()
{
    return (int)(Height * showMagnification);
}
int BasicObject::GetWidth()
{
    return (int)(Width * showMagnification);
}
bool BasicObject::isAlive()
{
    return is_alive;
}
bool BasicObject::isBreakable()
{
    return can_breakable;
}
}
