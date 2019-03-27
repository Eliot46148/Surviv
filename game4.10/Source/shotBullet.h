#pragma once
#include "BasicObject.h"
#include <math.h>
namespace game_framework {
	class shotBullet : public BasicObject {
	public:
		shotBullet();
		shotBullet(int,int);
		void OnMove();
		void LoadBitMap();
	private:
	};
}