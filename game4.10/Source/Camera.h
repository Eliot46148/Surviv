#pragma once
#include "BasicObject.h"
#include "items.h"
#include "Box.h"
#include "persona.h"

/* ����Camera */
namespace game_framework {
	class Camera {
	public:
		Camera();
		void OnMove();					// ����
		void setMovingMode(int, bool);  // �]�w���ʼҦ�
		void Retry();					// �bBeginstate���]�Ѽ�

        int GetX();						// �^��X�y��
        int GetY();						// �^��Y�y��
    private:
        int x, y;						// Camera�y��
        int speed;						// ���ʳt��
        bool isMovingUp, isMovingLeft, isMovingRight, isMovingDown;
};
}