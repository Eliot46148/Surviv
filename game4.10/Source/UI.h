#pragma once
#include "BasicObject.h"

namespace game_framework {
	class UI : public BasicObject {
	public:
		UI();
		void LoadBitMap();
		void OnShow();
		void ShowHealthBar();
		void TakePlayerInfo(int,int);
	private:
		int HP;
		int Ammo;
	};
}