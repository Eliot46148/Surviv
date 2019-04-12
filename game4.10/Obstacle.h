#pragma once
#include "BasicObject.h"

namespace game_framework {
	class Obstacle : public BasicObject
	{
	public:
		Obstacle();
		Obstacle(int x, int y);
		void LoadBitMap();
		void OnShow();
	};
}