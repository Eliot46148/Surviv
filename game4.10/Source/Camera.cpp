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

	for (unsigned int i = 0; i < Objects.size(); i++) {
		if (Objects.at(i) == NULL)
			Objects.erase(Objects.begin() + i);
		else
			Objects.at(i)->SetCamera(x, y);
	}
}

void game_framework::Camera::OnShow()
{
	for (unsigned i = 0; i < Objects.size(); i++)
		Objects.at(i)->OnShow();
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

void game_framework::Camera::AddObjects(BasicObject *object)
{
	Objects.push_back(object);
}

void game_framework::Camera::LoadBitMap(int index)
{
	Objects.at(index)->LoadBitMap();
}

int game_framework::Camera::GetObjectsSize()
{
	return Objects.size();
}

int game_framework::Camera::GetCameraX()
{
	return x;
}

int game_framework::Camera::GetCameraY()
{
	return y;
}
