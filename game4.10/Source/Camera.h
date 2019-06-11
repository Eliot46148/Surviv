#pragma once
#include "BasicObject.h"
#include "items.h"
#include "Box.h"
#include "persona.h"

/* 控制Camera */
namespace game_framework {
	class Camera {
	public:
		Camera();
		void OnMove();					// 移動
		void setMovingMode(int, bool);  // 設定移動模式
		void Retry();					// 在Beginstate重設參數

        int GetX();						// 回傳X座標
        int GetY();						// 回傳Y座標
    private:
        int x, y;						// Camera座標
        int speed;						// 移動速度
        bool isMovingUp, isMovingLeft, isMovingRight, isMovingDown;
};
}