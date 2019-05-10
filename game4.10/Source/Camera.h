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
		void OnShow();
		void setMovingMode(int, bool);
		void AddObjects(BasicObject*);
		void LoadBitMap(int);
		void Retry();

		int GetObjectsSize();

		int GetCameraX();
		int GetCameraY();
	private:
		int x, y;
		int speed;
		bool isMovingUp, isMovingLeft, isMovingRight, isMovingDown;

		/*地圖物件位址*/
		vector<BasicObject*> Objects;				
	};
}