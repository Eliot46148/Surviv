#pragma once
#include "BasicObject.h"
#include "items.h"
#include "Box.h"



namespace game_framework {
class persona : public BasicObject
{
    public:
        persona();
        void CatchItem(items take);
		bool HitObstacle(Box * box, int _where);
        virtual void LoadBitMap();
        virtual void OnShow();
		virtual void OnMove();						// Recoil計時和移動
		void returnBlood();
		
		bool Recoil();								// 擊發間隔時間

        void SetGetting(bool flag);
		void SetReloading(bool flag);
        void setCan_move(bool flag);
        void setBullet(int num);
		void setFacingPosition(double,double);
		void setDirection();
		void setActing(bool);
		void getDemage(int);
		void setHoldingItem(int);

		double getFacingX();
		double getFacingY();
		int getHasitemNum();
		int getHoldingItemID();
		int getBullet();
		int GetHP();
		int GetAmmo();

        bool isGetting();
		bool isReloading();
		bool isActing();
        bool isCan_Right();
        bool isCan_Left();
        bool isCan_Down();
        bool isCan_UP();

    private:
		CMovingBitmap bmp[3][25];		// 0:拳頭 1:槍
        bool is_Gettting = false;
		bool is_Reloading = false;
		bool is_acting = false;
        vector<items> hasitem;
		int holdingItem;							// 現在手持的武器
        int bullet;
		double facingX,facingY;
		int direction;
		int recoil_timer;
};
}