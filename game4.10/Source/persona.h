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
		void returnBlood();
		int ShowHP();
        void SetGetting(bool flag);
		void SetReloading(bool flag);
        void setCan_move(bool flag);
        void setBullet(int num);
		void setFacingPosition(double,double);
		void setDirection();
		double getFacingX();
		double getFacingY();
		int getHasitemNum();
		int getLastHasitemID();
		int getBullet();
        bool isGetting();
		bool isReloading();
        bool isCan_Right();
        bool isCan_Left();
        bool isCan_Down();
        bool isCan_UP();
    private:
		CMovingBitmap bmp[8];
        bool is_Gettting = false;
		bool is_Reloading = false;
        vector<items> hasitem;
        int bullet;
		double facingX,facingY;
		int direction;

};
}