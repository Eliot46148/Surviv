#pragma once
#include "BasicObject.h"

namespace game_framework {
	class UI : public BasicObject {
	public:
		UI();
		void LoadBitMap();
		void OnShow();
		void ShowHealthBar();
		void ShowInfo();
		void ShowItems();
		void TakePlayerInfo(int,int,int);
		void SetHealthStatus();
	private:
		int HP;
		int Ammo;
		int Enemy_Num;
		int HealthStatus;
		CMovingBitmap HealthBar[11];
		CMovingBitmap Ammo_img;
		CMovingBitmap ItemUI[3];
	};
}