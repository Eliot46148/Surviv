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
		void OnMove();
        void GetDamage(int);
        int moveDelay;
        void SetNearBox(Box* nbox);
        void ClearBBIPvector();
        void SetNearBullet(Bullet* nbullet);
        void SetNearItem(items* nitem);
		void SetCamera(int, int);
        void chouseMode();
        int rtNearPeople();
        void getNearItems();
        void getNeatBullet();
        void movetoplace();
        void Catchbullt(int bu);
        void CatchItem(items it);
        void setnearperson(persona* ps);
        int hasItom();
        int rtItom(int no);
        void setbullt(int num);
        int sizeitom();
        int hasbullet();
        bool isActing();
        int catchitemID();
        int Recoil_delay;
        vector<persona> nearPerson;
        vector<Box*> nearBox;
        int rrdelay = 0;
        bool tutchbox(Box* box, int _where);
        bool hitBox(Box* box);
    private:
		int camera_x, camera_y;
        CMovingBitmap bmp[8];
        bool is_Gettting = false;
        bool is_Reloading = false;
        vector<items> hasitem;
        vector<Bullet*> nearBuller;
        vector<items*> nearitems;
        int bullet;
        int direction;
        int random, movevector;
        int skin;
        bool is_acting;
		int recoil_timer;
};
}