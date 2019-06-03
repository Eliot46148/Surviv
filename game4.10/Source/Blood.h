#pragma once
#include "BasicObject.h"

namespace game_framework {
	class Blood : public BasicObject {
	public:
		Blood();
		void OnMove();
		void LoadBitMap();
		bool IsDead();
	private:
		int timer;
		bool is_Dead;	
		const int survival_time = 15;
	};
}