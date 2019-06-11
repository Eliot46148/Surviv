#pragma once
#include "BasicObject.h"
#include "items.h"
#include "Box.h"
#include "persona.h"

namespace game_framework {
	class Camera {
	public:
		Camera();
		void OnMove();
		void setMovingMode(int, bool);
		void Retry();

        int GetX();
        int GetY();
    private:
        int x, y;
        int speed;
        bool isMovingUp, isMovingLeft, isMovingRight, isMovingDown;
};
}