#pragma once
#include "BasicObject.h"
namespace game_framework {
class Texture : public BasicObject
{
    public:
        Texture(int x, int y, int skinid);
        void LoadBitMap();
    private:
        int skin;
};

}