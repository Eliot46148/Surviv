#pragma once
#include "BasicObject.h"
#include "items.h"
#include "Box.h"
#include "Map.h"


/* 控制角色行動 */
namespace game_framework {
class persona : public BasicObject
{
    public:
        persona();
        void CatchItem(items take);
        bool HitObstacle(Box* box, int _where);
        bool HitBorder(int _where);
        virtual void LoadBitMap();
        virtual void OnShow();						// 顯示
        virtual void OnMove();						// Recoil計時和移動
        void returnBlood();							// 密技：回血
        void Retry();
        bool Recoil();								// 擊發間隔時間
        void SetGetting(bool flag);					// 控制is_Getting
        void SetReloading(bool flag);				// 控制is_Reloading
        void setCan_move(bool flag);				// 控制can_move
        void setBullet(int num);					// 控制玩家儲備彈藥數量
		void setMegazine(int num);					// 控制玩家彈夾子彈數量
		void setFacingPosition(double,double);		// 控制facingX, facingY
		void setDirection();						// 控制角色面對方向
		void setActing(bool);						// 控制is_acting
		void getDemage(int);						// 受傷
		void setHoldingItem(int);					// 控制holdingItem
		void setBloodLock();						// 密技：鎖血

		double getFacingX();						// 回傳FacingX
		double getFacingY();						// 回傳FacingY
		int GetHitpointX();							// 回傳HitpointX
		int GetHitpointY();							// 回傳HitpointY
		int getHasitemNum();						// 回傳持有道具數量
		int* GetHasItemID();						// 回傳持有道具ID陣列
		int GetHoldingItem();						// 回傳holdingItem
		int getHoldingItemID();						// 回傳手持道具ID
		int getBullet();							// 回傳bullet
		int GetMegazine();							// 回傳megazine
		int GetHP();								// 回傳 hp
		int GetAmmo();								// 回傳bullet

		bool GetBloodLock();						// 回傳bloodLock
        bool isGetting();							// 回傳is_Getting
        bool isReloading();							// 回傳is_Reloading
        bool isActing();							// 回傳is_Acting
        bool isCan_Right();							// 回傳isMovingRight
        bool isCan_Left();							// 回傳isMovingLeft
        bool isCan_Down();							// 回傳isMovingDown
        bool isCan_UP();							// 回傳isMovingUP
		bool isMoving();							// 回傳是否正在移動
    private:
        CMovingBitmap bmp[4][25];		// 0:拳頭 1:槍 2:機槍 3:霰彈槍
        bool is_Gettting = false;		// 是否正在拾取道具
		bool is_Reloading = false;		// 是否正在裝填子彈
		bool is_acting = false;;		// 是否正在攻擊/使用道具
		bool bloodLock = false;			// 是否鎖血
        vector<items> hasitem;			// 所持物品
        int hasitemID[2] = { 0 };		// 所持物品ID陣列
        int holdingItem;				// 現在手持的武器
        int bullet;						// 儲備子彈
        int megazine;					// 彈夾裡的子彈
        double facingX, facingY;		// 面對位置座標
        int direction;					// 角色面對方向
        int recoil_timer;				// 後座計時器
        int reload_timer;				// 裝填子彈計時器
        int reload_time;				// 裝填子彈所需時間
};
}