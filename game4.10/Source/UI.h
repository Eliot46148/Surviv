#pragma once
#include "BasicObject.h"

namespace game_framework {
	class UI : public BasicObject {
	public:
		UI();
		void LoadBitMap();
		void OnShow();
		void ShowHealthBar();								// ��� HealthBar
		void ShowInfo();									// �Ѿl�ĤH
		void ShowItems();									// �����Z��
		void ShowBullets();									// �����l�u
		void TakePlayerInfo(int,int,int,int*,int);			// ���� HP, �l�u�ƥ�, �ĤH�ƥ�, hasitemID, holdingitem ��ơA�éI�s SetHealthStatus()
		void SetHealthStatus();								// ���� HealthBar ���A
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