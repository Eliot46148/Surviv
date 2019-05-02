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
		int itemsID;										// ID ®±ÀY   : 0
															//	  ¤âºj   : 1
															//	  ¾÷ºj   : 2
															//	  ÄÅ¼uºj : 3
};
}