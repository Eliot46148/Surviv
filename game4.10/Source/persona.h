#pragma once
#include "BasicObject.h"
#include "items.h"


namespace game_framework {
class persona : public BasicObject
{
    public:
        persona();
        void CatchItem(items take);
        virtual void LoadBitMap();
        virtual void OnShow();
        void SetGetting(bool flag);
		void SetReloading(bool flag);
        void setCan_move(bool flag);
        void setBullet(int num);
		void setFacingPosition(int,int);
		int getFacingX();
		int getFacingY();
        bool isGetting();
		bool isReloading();
        bool isCan_Right();
        bool isCan_Left();
        bool isCan_Down();
        bool isCan_UP();
    private:
        bool is_Gettting = false;
		bool is_Reloading = false;
        vector<items> hasitem;
        int bullet;
		int facingX,facingY;

};
}