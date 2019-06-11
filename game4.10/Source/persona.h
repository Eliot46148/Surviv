#pragma once
#include "BasicObject.h"
#include "items.h"
#include "Box.h"
#include "Map.h"


/* ������� */
namespace game_framework {
class persona : public BasicObject
{
    public:
        persona();
        void CatchItem(items take);
        bool HitObstacle(Box* box, int _where);
        bool HitBorder(int _where);
        virtual void LoadBitMap();
        virtual void OnShow();						// ���
        virtual void OnMove();						// Recoil�p�ɩM����
        void returnBlood();							// �K�ޡG�^��
        void Retry();
        bool Recoil();								// ���o���j�ɶ�
        void SetGetting(bool flag);					// ����is_Getting
        void SetReloading(bool flag);				// ����is_Reloading
        void setCan_move(bool flag);				// ����can_move
        void setBullet(int num);					// ����a�x�Ƽu�ļƶq
		void setMegazine(int num);					// ����a�u���l�u�ƶq
		void setFacingPosition(double,double);		// ����facingX, facingY
		void setDirection();						// ����⭱���V
		void setActing(bool);						// ����is_acting
		void getDemage(int);						// ����
		void setHoldingItem(int);					// ����holdingItem
		void setBloodLock();						// �K�ޡG���

		double getFacingX();						// �^��FacingX
		double getFacingY();						// �^��FacingY
		int GetHitpointX();							// �^��HitpointX
		int GetHitpointY();							// �^��HitpointY
		int getHasitemNum();						// �^�ǫ����D��ƶq
		int* GetHasItemID();						// �^�ǫ����D��ID�}�C
		int GetHoldingItem();						// �^��holdingItem
		int getHoldingItemID();						// �^�Ǥ���D��ID
		int getBullet();							// �^��bullet
		int GetMegazine();							// �^��megazine
		int GetHP();								// �^�� hp
		int GetAmmo();								// �^��bullet

		bool GetBloodLock();						// �^��bloodLock
        bool isGetting();							// �^��is_Getting
        bool isReloading();							// �^��is_Reloading
        bool isActing();							// �^��is_Acting
        bool isCan_Right();							// �^��isMovingRight
        bool isCan_Left();							// �^��isMovingLeft
        bool isCan_Down();							// �^��isMovingDown
        bool isCan_UP();							// �^��isMovingUP
		bool isMoving();							// �^�ǬO�_���b����
    private:
        CMovingBitmap bmp[4][25];		// 0:���Y 1:�j 2:���j 3:�żu�j
        bool is_Gettting = false;		// �O�_���b�B���D��
		bool is_Reloading = false;		// �O�_���b�˶�l�u
		bool is_acting = false;;		// �O�_���b����/�ϥιD��
		bool bloodLock = false;			// �O�_���
        vector<items> hasitem;			// �ҫ����~
        int hasitemID[2] = { 0 };		// �ҫ����~ID�}�C
        int holdingItem;				// �{�b������Z��
        int bullet;						// �x�Ƥl�u
        int megazine;					// �u���̪��l�u
        double facingX, facingY;		// �����m�y��
        int direction;					// ���⭱���V
        int recoil_timer;				// ��y�p�ɾ�
        int reload_timer;				// �˶�l�u�p�ɾ�
        int reload_time;				// �˶�l�u�һݮɶ�
};
}