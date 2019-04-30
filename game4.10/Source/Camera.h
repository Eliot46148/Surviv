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
		void AddObjects(BasicObject*);
	private:
		int x, y;
		int speed;
		bool isMovingUp, isMovingLeft, isMovingRight,isMovingDown;

		/*地圖物件位址*/
		vector<BasicObject*> Objects;				
	};
}