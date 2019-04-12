#pragma once
#include "BasicObject.h"

namespace game_framework {
class Bullet : public BasicObject
{
    public:
        Bullet();
        Bullet(int x, int y);
        void LoadBitMap();
};
}