#pragma once
#include "BasicObject.h"
/* ±±¨î¦a¹Ï */
namespace game_framework {
class Map : public BasicObject
{
    public:
        Map();
        void LoadBitMap();
        void OnShow();
    private:
};
}