#pragma once
#include "BasicObject.h"
/* ����a�� */
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