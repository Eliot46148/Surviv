#pragma once
#include "BasicObject.h"

/* ����a�ϤW���l�u */
namespace game_framework {
class Bullet : public BasicObject
{
    public:
        Bullet();
        Bullet(int x, int y);
        void LoadBitMap();
};
}