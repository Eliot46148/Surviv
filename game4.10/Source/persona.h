#pragma once
#include "BasicObject.h"
#include "items.h"
#include "Box.h"
#include "Map.h"



namespace game_framework {
class persona : public BasicObject
{
    public:
        persona();
        void CatchItem(items take);
		bool HitObstacle(Box * box, int _where);
		bool HitBorder(int _where);
        virtual void LoadBitMap();
        virtual void OnShow();
		virtual void OnMove();						// Recoil�p�ɩM����
		void returnBlood();
		void Retry();

		
		bool Recoil();								// ���o���j�ɶ�

        void SetGetting(bool flag);
		void SetReloading(bool flag);
        void setCan_move(bool flag);
        void setBullet(int num);
		void setMegazine(int num);
		void setFacingPosition(double,double);
		void setDirection();
		void setActing(bool);
		void getDemage(int);
		void setHoldingItem(int);

		double getFacingX();
		double getFacingY();
		int GetHitpointX();
		int GetHitpointY();
		int getHasitemNum();
		int* GetHasItemID();
		int GetHoldingItem();
		int getHoldingItemID();
		int getBullet();
		int GetMegazine();
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
		CMovingBitmap bmp[4][25];		// 0:���Y 1:�j 2:���j 3:�żu�j
        bool is_Gettting = false;
		bool is_Reloading = false;
		bool is_acting = false;
        vector<items> hasitem;
		int hasitemID[2] = { 0 };
		int holdingItem;				// �{�b������Z��
        int bullet;						// �x�Ƥl�u
		int megazine;					// �u���̪��l�u
		double facingX,facingY;
		int direction;
		int recoil_timer;
		int reload_timer;
};
}