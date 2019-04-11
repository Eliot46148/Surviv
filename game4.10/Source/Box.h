#pragma once
#include "BasicObject.h"

namespace game_framework {
class Box : public BasicObject
{
    public:
        Box();
        Box(int x, int y);
        void LoadBitMap();
        int ShowHP();
        void GetDamage(int);
};
}