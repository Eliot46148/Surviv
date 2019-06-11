#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Camera.h"
#include "Box.h"
#include "Enemy.h"

game_framework::Camera::Camera()
{
    speed = DEFAULT_OBJECTIVE_SPEED;
    isMovingUp = isMovingLeft = isMovingRight = isMovingDown = false;
    x = y = 0;
}

void game_framework::Camera::OnMove()
{
    if (isMovingLeft)
        x -= speed;

    if (isMovingRight)
        x += speed;

    if (isMovingUp)
        y -= speed;

    if (isMovingDown)
        y += speed;

}

void game_framework::Camera::setMovingMode(int path, bool flag)
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

void game_framework::Camera::Retry()
{
    speed = DEFAULT_OBJECTIVE_SPEED;
    isMovingUp = isMovingLeft = isMovingRight = isMovingDown = false;
    x = y = 0;
}

int game_framework::Camera::GetX()
{
    return x;
}

int game_framework::Camera::GetY()
{
    return y;
}
