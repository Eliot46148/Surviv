#pragma once
#include "BasicObject.h"
#include <math.h>
#include "Box.h"
#include "persona.h"
#include "Enemy.h"
/* 控制射出子彈 */
namespace game_framework {
class shotBullet : public BasicObject
{
    public:
        shotBullet();
        shotBullet(int, int, int, int, int, int, int, int);
        void OnMove();											// 移動
        void LoadBitMap();
        bool HitPlayer(persona* player);						// 擊中玩家
        bool HitEnemy(Enemy* enemy);							// 擊中敵人
        bool HitObstacle(Box* box);								// 擊中障礙物
        bool HitSomething(int, int, int, int);					// 是否擊中碰撞判斷
        int ShowDamage();										// 回傳damage
        int getshooter();										// 回傳shooter
    private:
        int damage;		// 子彈傷害
        int shooter;	// 射出子彈的人
        int ID;         // 1： 紅(玩家) , 2： 藍(敵人)
};
}
