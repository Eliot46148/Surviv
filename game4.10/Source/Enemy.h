#pragma once
#include "BasicObject.h"
#include "items.h"
#include "Box.h"
#include "persona.h"

namespace game_framework {
	class Enemy :public persona {
	public:
		Enemy();
		void LoadBitMap();
		void OnShow();
		void GetDamage(int);
	private:
		CMovingBitmap bmp[8];
		bool is_Gettting = false;
		bool is_Reloading = false;
		vector<items> hasitem;
		int bullet;
		int facingX, facingY;
		int direction;
	};
}