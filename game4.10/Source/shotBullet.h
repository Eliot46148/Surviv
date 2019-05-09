#pragma once
#include "BasicObject.h"
#include <math.h>
#include "Box.h"
#include "persona.h"

namespace game_framework {
	class shotBullet : public BasicObject {
	public:
		shotBullet();
		shotBullet(int,int,int,int,int,int,int);
		void OnMove();
		void LoadBitMap();
		bool HitPlayer(persona *player);
		bool HitObstacle(Box *box);
		bool HitSomething(int,int,int,int);
		int ShowDamage();
		int getshooter();
	private:
		int damage;
		int shooter;
	};
}
