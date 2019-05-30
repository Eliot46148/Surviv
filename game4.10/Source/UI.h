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
		void TakePlayerInfo(int,int,int,int,int*,int,bool);		// 接收 HP, 儲備數目, 彈夾子彈數目, 敵人數目, hasitemID, holdingitem 資料，並呼叫 SetHealthStatus()
		void SetHealthStatus();								// 切換 HealthBar 狀態
		void Showloading();									// 顯示 Loading
	private:
		int HP;
		int Ammo;
		int Megazine;
		int Enemy_Num;
		int HealthStatus;
		int *hasitemsID;
		int holdingitem;
		int Loading_Timer;			   // loading 計數器
		int Loading_Index;			   // loading 現在的圖片編號

		bool is_Reloading;

		CMovingBitmap HealthBar[11];
		CMovingBitmap Ammo_img;
		CMovingBitmap ItemUI[2][2];
		CMovingBitmap items_img[3];    //  0:手槍, 1:機槍, 2:霰彈槍
		CMovingBitmap bullet_img[3];
		CMovingBitmap loading[4];
	};
}