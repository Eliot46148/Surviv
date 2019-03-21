#pragma once
#include "BasicObject.h"
namespace game_framework {
class items : public BasicObject
{
    public:
		items();
		void LoadBitMap();
		void OnShow();
};
}