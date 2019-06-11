#pragma once
#include "BasicObject.h"

/* 控制地圖上的子彈 */
namespace game_framework {
class Bullet : public BasicObject
{
    public:
        Bullet();
        Bullet(int x, int y);
        void LoadBitMap();
};
}