#pragma once
#include "BasicObject.h"

namespace game_framework {
	class Map : public BasicObject{
	public:
		Map();
		void LoadBitMap();
		void OnShow();
	private:
	};
}