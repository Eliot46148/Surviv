#pragma once
#include "BasicObject.h"

namespace game_framework {
class Box : public BasicObject {
    public:
        Box();
		void LoadBitMap();
		void OnShow();
};
}