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
		void TakePlayerInfo(int,int,int,int,int*,int,bool);		// ���� HP, �x�Ƽƥ�, �u���l�u�ƥ�, �ĤH�ƥ�, hasitemID, holdingitem ��ơA�éI�s SetHealthStatus()
		void SetHealthStatus();								// ���� HealthBar ���A
		void Showloading();									// ��� Loading
	private:
		int HP;
		int Ammo;
		int Megazine;
		int Enemy_Num;
		int HealthStatus;
		int *hasitemsID;
		int holdingitem;
		int Loading_Timer;			   // loading �p�ƾ�
		int Loading_Index;			   // loading �{�b���Ϥ��s��

		bool is_Reloading;

		CMovingBitmap HealthBar[11];
		CMovingBitmap Ammo_img;
		CMovingBitmap ItemUI[2][2];
		CMovingBitmap items_img[3];    //  0:��j, 1:���j, 2:�żu�j
		CMovingBitmap bullet_img[3];
		CMovingBitmap loading[4];
	};
}