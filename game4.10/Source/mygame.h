#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"
#include "Map.h"
#include "Box.h"
#include "persona.h"
#include "items.h"
#include "Bullet.h"
#include "shotBullet.h"
#include <math.h>
#include "Texture.h"
#include "Enemy.h"
#include "Camera.h"
#include "UI.h"

namespace game_framework {

enum AUDIO_ID  				// 定義各種音效的編號
{
    AUDIO_DING,				// 0
    AUDIO_LAKE,				// 1
    AUDIO_NTUT				// 2
};
static bool isWin = false;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
// 每個Member function的Implementation都要弄懂
/////////////////////////////////////////////////////////////////////////////

class CGameStateInit : public CGameState
{
    public:
        CGameStateInit(CGame* g);
        void OnInit();  								// 遊戲的初值及圖形設定
        void OnBeginState();							// 設定每次重玩所需的變數
        void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
        void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
    protected:
        void OnShow();									// 顯示這個狀態的遊戲畫面
		void OnMove();
    private:
        CMovingBitmap logo;								// csie的logo
		int delay = 0;
		bool showTip = true;
};
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
// 每個Member function的Implementation都要弄懂
/////////////////////////////////////////////////////////////////////////////

class CGameStateRun : public CGameState
{
    public:
        CGameStateRun(CGame* g);
        ~CGameStateRun();
        void OnBeginState();							// 設定每次重玩所需的變數
        void ChangeMovingMode(int _where, bool type);
        void OnInit();  								// 遊戲的初值及圖形設定
        void OnKeyDown(UINT, UINT, UINT);
        void OnKeyUp(UINT, UINT, UINT);
        void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
        void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
        void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作
        void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
        void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void Cheat();									// 測試用 直接勝利
    protected:
        void OnMove();									// 移動遊戲元素
        void OnShow();									// 顯示這個狀態的遊戲畫面
    private:
        CMovingBitmap dot;							// 角落圖
        Camera camera;
        Map map;
		UI ui;
        vector<Box> box;
        vector<items> item;
        persona player1;
        vector<Bullet> bullet;
        vector<shotBullet> shotbullets;
        vector<Texture> texture;
        vector<Enemy> enemy;
		bool firstlife;		// 是否為第一次進入此state
};

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
// 每個Member function的Implementation都要弄懂
/////////////////////////////////////////////////////////////////////////////

class CGameStateOver : public CGameState
{
    public:
        CGameStateOver(CGame* g);
        void OnBeginState();							// 設定每次重玩所需的變數
        void OnInit();
    protected:
        void OnMove();									// 移動遊戲元素
        void OnShow();									// 顯示這個狀態的遊戲畫面
		void OnLButtonDown(UINT nFlags, CPoint point);
    private:
        int counter;	// 倒數之計數器
		CMovingBitmap logo[2];
		int delay = 0;
		bool showTip = true;
};

}
