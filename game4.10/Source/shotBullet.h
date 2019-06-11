#pragma once
#include "BasicObject.h"
#include <math.h>
#include "Box.h"
#include "persona.h"
#include "Enemy.h"
/* ����g�X�l�u */
namespace game_framework {
class shotBullet : public BasicObject
{
    public:
        shotBullet();
        shotBullet(int, int, int, int, int, int, int, int);
        void OnMove();											// ����
        void LoadBitMap();
        bool HitPlayer(persona* player);						// �������a
        bool HitEnemy(Enemy* enemy);							// �����ĤH
        bool HitObstacle(Box* box);								// ������ê��
        bool HitSomething(int, int, int, int);					// �O�_�����I���P�_
        int ShowDamage();										// �^��damage
        int getshooter();										// �^��shooter
    private:
        int damage;		// �l�u�ˮ`
        int shooter;	// �g�X�l�u���H
        int ID;         // 1�G ��(���a) , 2�G ��(�ĤH)
};
}
