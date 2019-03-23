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
        void setCan_move(bool flag);
        void setBullet(int num);
        bool isGetting();
        bool isCan_Right();
        bool isCan_Left();
        bool isCan_Down();
        bool isCan_UP();
    private:
        bool is_Gettting = false;
        vector<items> hasitem;
        int bullet;

};
}