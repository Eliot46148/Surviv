#pragma once
#include "BasicObject.h"

namespace game_framework {
class items : public BasicObject
{
    public:
        items();
        items(int x, int y, int id, float showsize);
        void LoadBitMap();
		int getID();
    private:
        int itemsdamage;
		int itemsID;										// 武器ID 拳頭   : 0
															//		  手槍   : 1
															//		  機槍   : 2
															//		  霰彈槍 : 3
};
}