#pragma once
#include "BasicObject.h"

/* ����a�ϤW���Z���M�D�� */
namespace game_framework {
class items : public BasicObject
{
    public:
        items();
        items(int x, int y, int id, float showsize);
        void LoadBitMap();
        int getID();		// �^��itemsID
    private:
        int itemsdamage;
        int itemsID;										
		// ID ���Y   : 0
        //	  ��j   : 1
        //	  ���j   : 2
        //	  �żu�j : 3
        //    �^�a   : 4
};
}