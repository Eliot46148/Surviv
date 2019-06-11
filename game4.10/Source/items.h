#pragma once
#include "BasicObject.h"

/* 控制地圖上的武器和道具 */
namespace game_framework {
class items : public BasicObject
{
    public:
        items();
        items(int x, int y, int id, float showsize);
        void LoadBitMap();
        int getID();		// 回傳itemsID
    private:
        int itemsdamage;
        int itemsID;										
		// ID 拳頭   : 0
        //	  手槍   : 1
        //	  機槍   : 2
        //	  霰彈槍 : 3
        //    繃帶   : 4
};
}