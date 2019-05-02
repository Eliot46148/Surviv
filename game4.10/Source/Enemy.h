#pragma once
#include "BasicObject.h"
#include "items.h"
#include "Box.h"
#include "persona.h"
#include "Box.h"
#include "Bullet.h"

namespace game_framework {
	class Enemy :public persona {
	public:
		Enemy();
		Enemy(int, int, int);
		void LoadBitMap();
		void OnShow();
		void GetDamage(int);
		int moveDelay;
		void SetNearBox(Box *nbox);
		void ClearBBIvector();
		void SetNearBullet(Bullet *nbullet);
		void SetNearItem(items *nitem);
		void chouseMode();
	private:
		CMovingBitmap bmp[8];
		bool is_Gettting = false;
		bool is_Reloading = false;
		vector<items> hasitem;
		vector<Box*> nearBox;
		vector<Bullet*> nearBuller;
		vector<items*> nearitems;
		int bullet;
		int direction;
		int skin;
	};
}