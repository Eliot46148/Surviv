#pragma once
#include "BasicObject.h"

namespace game_framework {
class items : public BasicObject
{
    public:
        items();
        items(int x, int y);
        void LoadBitMap();
        void OnShow();
    private:
        int damage = 10;
};
}