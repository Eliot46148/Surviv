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
		int itemsID;										// �Z��ID ���Y   : 0
															//		  ��j   : 1
															//		  ���j   : 2
															//		  �żu�j : 3
};
}