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
		void ShowBullets();
		void TakePlayerInfo(int,int,int,int*,int);
		void SetHealthStatus();
	private:
		int HP;
		int Ammo;
		int Enemy_Num;
		int HealthStatus;
		int *hasitemsID;
		int holdingitem;
		CMovingBitmap HealthBar[11];
		CMovingBitmap Ammo_img;
		CMovingBitmap ItemUI[2][2];
		CMovingBitmap items_img[3];    //  0:��j, 1:���j, 2:�żu�j
		CMovingBitmap bullet_img[3];
	};
}