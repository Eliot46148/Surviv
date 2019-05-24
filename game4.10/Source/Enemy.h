#pragma once
#include "BasicObject.h"
#include "items.h"
#include "Box.h"
#include "persona.h"
#include "Box.h"
#include "Bullet.h"

namespace game_framework {
class Enemy : public persona
{
    public:
        Enemy();
        Enemy(int, int, int);
        void LoadBitMap();
        void OnShow();
        void GetDamage(int);
        int moveDelay;
        void SetNearBox(Box* nbox);
        void ClearBBIPvector();
        void SetNearBullet(Bullet* nbullet);
        void SetNearItem(items* nitem);
        void chouseMode();
        int rtNearPeople();
        void getNearItems();
        void getNeatBullet();
        void movetoplace();
        void Catchbullt(int bu);
        void CatchItem(items it);
		void setnearperson(persona *ps);
        int hasItom();
        void setbullt(int num);
        int hasbullet();
		bool isActing();
		int catchitemID();
		int Recoil_delay;
		vector<persona> nearPerson;
		int rrdelay = 0;
    private:
        CMovingBitmap bmp[8];
        bool is_Gettting = false;
        bool is_Reloading = false;
        vector<items> hasitem;
        vector<Box*> nearBox;
        vector<Bullet*> nearBuller;
        vector<items*> nearitems;
        int bullet;
        int direction;
        int random, movevector;
        int skin;
		bool is_acting;
};
}