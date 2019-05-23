#pragma once
#include "BasicObject.h"

namespace game_framework {
	class UI : public BasicObject {
	public:
		UI();
		void LoadBitMap();
		void OnShow();
		void ShowHealthBar();								// 顯示 HealthBar
		void ShowInfo();									// 剩餘敵人
		void ShowItems();									// 持有武器
		void ShowBullets();									// 持有子彈
		void TakePlayerInfo(int,int,int,int*,int);			// 接收 HP, 子彈數目, 敵人數目, hasitemID, holdingitem 資料，並呼叫 SetHealthStatus()
		void SetHealthStatus();								// 切換 HealthBar 狀態
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
		CMovingBitmap items_img[3];    //  0:手槍, 1:機槍, 2:霰彈槍
		CMovingBitmap bullet_img[3];
	};
}