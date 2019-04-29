#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "BasicObject.h"
#include "persona.h"


namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame* g)
    : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
    ShowInitProgress(0);	// 一開始的loading進度為0%
    //
    // 載入資料的地方
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_ESC = 27;
    const char KEY_SPACE = ' ';

    if (nChar == KEY_SPACE)
        GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
    else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
        PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// 關閉遊戲
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
    GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
    // Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
    //
    CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
    fp = pDC->SelectObject(&f);					// 選用 font f
    pDC->SetBkColor(RGB(0, 0, 0));
    pDC->SetTextColor(RGB(255, 255, 0));
    pDC->TextOut(120, 220, "Please click mouse or press SPACE to begin.");
    pDC->TextOut(5, 395, "Press Ctrl-F to switch in between window mode and full screen mode.");

    if (ENABLE_GAME_PAUSE)
        pDC->TextOut(5, 425, "Press Ctrl-Q to pause the Game.");

    pDC->TextOut(5, 455, "Press Alt-F4 or ESC to Quit.");
    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame* g)
    : CGameState(g)
{
}

void CGameStateOver::OnMove()
{
    counter--;

    if (counter < 0)
        GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
    counter = 30 * 5; // 5 seconds
}

void CGameStateOver::OnInit()
{
    ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
    //
    // 開始載入結束後要用到的資料??
    //
    ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
    CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
    fp = pDC->SelectObject(&f);					// 選用 font f
    pDC->SetBkColor(RGB(0, 0, 0));
    pDC->SetTextColor(RGB(255, 255, 0));
    char str[80];								// Demo 數字對字串的轉換
    sprintf(str, "Game Over ! (%d)", counter / 30);
    pDC->TextOut(240, 210, str);
    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame* g)
    : CGameState(g)  //初始化設定
{
    box.push_back(Box(100, 100));								// 加入箱子
    // box.push_back(Box(200, 200));								// 加入箱子
    item.push_back(items(450, 400, 1, (float)0.4));				// 加入手槍
    item.push_back(items(450, 450, 1, (float)0.4));				// 加入手槍
    item.push_back(items(450, 500, 2, (float)0.4));				// 加入機槍
    item.push_back(items(450, 550, 2, (float)0.4));				// 加入機槍
    enemy.push_back(Enemy(520, 240, 1));
    //enemy.push_back(Enemy(490, 150, 2));
    //enemy.push_back(Enemy(400, 150, 3));

    for (int i = 0; i < 60; i++)
        bullet.push_back(Bullet(rand() % (2780 + 1), rand() % (2780 + 1)));
}

CGameStateRun::~CGameStateRun()
{
    //delete [] ball;
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::ChangeMovingMode(int _where, bool type)
{
    for (int j = 0; j < static_cast<int>(box.size()); j++)
        box[j].setMovingMode(_where, type);

    for (int j = 0; j < static_cast<int>(item.size()); j++)
        item[j].setMovingMode(_where, type);

    for (int j = 0; j < static_cast<int>(bullet.size()); j++)
        bullet[j].setMovingMode(_where, type);

    for (int j = 0; j < static_cast<int>(texture.size()); j++)
        texture[j].setMovingMode(_where, type);

    for (int j = 0; j < static_cast<int>(enemy.size()); j++)
        enemy[j].setMovingMode(_where, type);
}

void CGameStateRun::OnMove()											// 移動遊戲元素
{
	SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));					// 鼠標設定
	bool isshow;
	int randmov;

	for (int i = 1; i < 5; i++)
		player1.setMovingMode(i, 1);

	for (int i = 0; i < static_cast<int>(enemy.size()); i++)
	{
		if (enemy.at(i).moveDelay != 0)
		{
			enemy.at(i).setMovingMode(randmov, 1);
			enemy.at(i).moveDelay--;
		}
		else
		{
			enemy.at(i).moveDelay = 30;
			randmov = rand() % 5;
			enemy.at(i).setMovingMode(randmov, 1);
		}
	}

	for (int i = 0; i < static_cast<int>(shotbullets.size()); i++)
	{
		isshow = 1;

		for (int j = 0; j < static_cast<int>(enemy.size()); j++)
			if (static_cast<int>(shotbullets.size()) != i && shotbullets.at(i).HitPlayer(&enemy.at(j)))
			{
				isshow = 0;
				enemy.at(j).GetDamage(shotbullets.at(i).ShowDamage());
				shotbullets.erase(shotbullets.begin() + i);

				if (enemy.at(j).ShowHP() <= 0)
				{
					texture.push_back(Texture(enemy.at(j).GetX(), enemy.at(j).GetY(), 2));
					enemy.erase(enemy.begin() + j);
				}
			}

		if (isshow)
			for (int j = 0; j < static_cast<int>(box.size()); j++)
			{
				if (static_cast<int>(shotbullets.size()) == 0)
					break;

				if (shotbullets.at(i).HitObstacle(&box.at(j)))
				{
					box.at(j).GetDamage(shotbullets.at(i).ShowDamage());
					shotbullets.erase(shotbullets.begin() + i);

					if (box.at(j).ShowHP() <= 0)
					{
						texture.push_back(Texture(box.at(j).GetX(), box.at(j).GetY(), 1));
						box.erase(box.begin() + j);
					}
				}
			}
	}

	for (int i = 0; i < static_cast<int>(box.size()); i++)
		for (int j = 1; j < 5; j++)
			if (player1.HitObstacle(&box.at(i), j))
			{
				player1.setMovingMode(j, 0);
				map.setMovingMode(j, 0);
				ChangeMovingMode(j, 0);
			}

	map.OnMove();
	player1.OnMove();

	for (int i = 0; i < static_cast<int>(box.size()); i++)
		box.at(i).OnMove();

	for (int i = 0; i < static_cast<int>(item.size()); i++)
		item.at(i).OnMove();

	for (int i = 0; i < static_cast<int>(bullet.size()); i++)
		bullet.at(i).OnMove();

	for (int i = 0; i < static_cast<int>(shotbullets.size()); i++)
		shotbullets.at(i).OnMove();

	for (int i = 0; i < static_cast<int>(texture.size()); i++)
		texture.at(i).OnMove();

	for (int i = 0; i < static_cast<int>(enemy.size()); i++)
		enemy.at(i).OnMove();

	if (player1.isActing()){
		if (!player1.isReloading() && player1.getBullet() > 0 && player1.getHoldingItemID() == 2 && !player1.Recoil())
		{
			player1.setBullet(-1);
			shotbullets.push_back(shotBullet(int(player1.getFacingX()), int(player1.getFacingY())));
		}
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
    //
    // 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
    //     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
    //
    ShowInitProgress(33);
    ShowInitProgress(50);
    map.LoadBitMap();

    for (int i = 0; i < static_cast<int>(box.size()); i++)
        box[i].LoadBitMap();

    for (int i = 0; i < static_cast<int>(item.size()); i++)
        item[i].LoadBitMap();

    for (int i = 0; i < static_cast<int>(bullet.size()); i++)
        bullet[i].LoadBitMap();

    for (int i = 0; i < static_cast<int>(enemy.size()); i++)
        enemy[i].LoadBitMap();

    player1.LoadBitMap();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT  = 0x41;		 // keyboard  [A]
    const char KEY_UP    = 0x57;		 // keyboard  [W]
    const char KEY_RIGHT = 0x44;		 // keyboard  [D]
    const char KEY_DOWN  = 0x53;		 // keyboard  [S]
    const char KEY_GET = 0x46;			 // keyboard  [F]
    const char KEY_RTBLOOD = 0x4F;		 // keyboard  [F]
	const char KEY_First = 0x31;		 // keyboard  [1]
	const char KEY_Second = 0x32;		 // keyboard  [2]
	const char KEY_Fist = 0x33;			 // keyboard  [3]
	//const char KEY_Grenade = 0x21;	 // keyboard  [4]

    if (nChar == KEY_LEFT && player1.isCan_Left())
    {
        map.setMovingMode(4, 1);
        ChangeMovingMode(4, 1);

        for (int i = 0; i < static_cast<int>(shotbullets.size()); i++)
            shotbullets[i].setMovingMode(4, 1);
    }

    if (nChar == KEY_RIGHT && player1.isCan_Right())
    {
        map.setMovingMode(3, 1);
        ChangeMovingMode(3, 1);

        for (int i = 0; i < static_cast<int>(shotbullets.size()); i++)
            shotbullets[i].setMovingMode(3, 1);
    }

    if (nChar == KEY_UP && player1.isCan_UP())
    {
        map.setMovingMode(2, 1);
        ChangeMovingMode(2, 1);

        for (int i = 0; i < static_cast<int>(shotbullets.size()); i++)
            shotbullets[i].setMovingMode(2, 1);
    }

    if (nChar == KEY_DOWN && player1.isCan_Down())
    {
        map.setMovingMode(1, 1);
        ChangeMovingMode(1, 1);

        for (int i = 0; i < static_cast<int>(shotbullets.size()); i++)
            shotbullets[i].setMovingMode(1, 1);
    }

    if (nChar == KEY_GET)
    {
        player1.SetGetting(true);
    }

    if (nChar == KEY_RTBLOOD)
    {
        enemy.at(0).returnBlood();
    }


	//////////     切換武器       ///////////////////////////////////////
	if (nChar == KEY_First && player1.getHasitemNum() >= 1)
		player1.setHoldingItem(0);
	if (nChar == KEY_Second && player1.getHasitemNum() >= 2)
		player1.setHoldingItem(1);
	if (nChar == KEY_Fist)
		player1.setHoldingItem(2);
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT  = 0x41; // keyboard  [A]
    const char KEY_UP = 0x57;    // keyboard  [W]
    const char KEY_RIGHT = 0x44; // keyboard  [D]
    const char KEY_DOWN = 0x53;  // keyboard  [S]
    const char KEY_GET = 0x46;   // keyboard  [F]

    if (nChar == KEY_LEFT)
    {
        map.setMovingMode(4, 0);
        ChangeMovingMode(4, 0);

        for (int i = 0; i < static_cast<int>(shotbullets.size()); i++)
            shotbullets[i].setMovingMode(4, 0);
    }

    if (nChar == KEY_RIGHT)
    {
        map.setMovingMode(3, 0);
        ChangeMovingMode(3, 0);

        for (int i = 0; i < static_cast<int>(shotbullets.size()); i++)
            shotbullets[i].setMovingMode(3, 0);
    }

    if (nChar == KEY_UP)
    {
        map.setMovingMode(2, 0);
        ChangeMovingMode(2, 0);

        for (int i = 0; i < static_cast<int>(shotbullets.size()); i++)
            shotbullets[i].setMovingMode(2, 0);
    }

    if (nChar == KEY_DOWN)
    {
        map.setMovingMode(1, 0);
        ChangeMovingMode(1, 0);

        for (int i = 0; i < static_cast<int>(shotbullets.size()); i++)
            shotbullets[i].setMovingMode(1, 0);
    }

    if (nChar == KEY_GET)
    {
        for (int i = 0; i < static_cast<int>(item.size()); i++)
            if (player1.isGetting() && player1.getHasitemNum()< 2 && (item.at(i).GetX() >= player1.GetX() && item.at(i).GetX()  <= player1.GetX() + player1.GetWidth()) && (item.at(i).GetY() >= player1.GetY() && item.at(i).GetY()  <= player1.GetY() + player1.GetHeight()))
            {
                item.at(i).SetAlive(false);
                player1.CatchItem(item.at(i));
                item.erase(item.begin() + i);
            }

        for (int i = 0; i < static_cast<int>(bullet.size()); i++)
            if (player1.isGetting() && (bullet.at(i).GetX() >= player1.GetX() && bullet.at(i).GetX() <= player1.GetX() + player1.GetWidth()) && (bullet.at(i).GetY() >= player1.GetY() && bullet.at(i).GetY() <= player1.GetY() + player1.GetHeight()))
            {
                bullet.at(i).SetAlive(false);
                bullet.erase(bullet.begin() + i);
                player1.setBullet(30);
            }

        player1.SetGetting(false);
    }
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
    if (player1.getHasitemNum() != 0)
    {
        if (!player1.isReloading() && player1.getBullet() > 0 )
        {	
			if (player1.getHoldingItemID() == 1) {
				player1.SetReloading(true);
				player1.setBullet(-1);
				shotbullets.push_back(shotBullet(int(player1.getFacingX()), int(player1.getFacingY())));
			}
        }
    }
	player1.setActing(true);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
    player1.SetReloading(false);
	player1.setActing(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
    int x = point.x - (SIZE_X / 2);
    int y = point.y - (SIZE_Y / 2);
    double r = sqrt(x * x + y * y);
    player1.setFacingPosition(x / r * 10, y / r * 10);
    player1.setDirection();
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
    //
    //  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
    //        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
    //        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
    //
    map.OnShow();

    for (int i = 0; i < static_cast<int>(texture.size()); i++)
        texture[i].OnShow();

    for (int i = 0; i < static_cast<int>(enemy.size()); i++)
        enemy[i].OnShow();

    player1.OnShow();

    for (int i = 0; i < static_cast<int>(box.size()); i++)
        box[i].OnShow();

    for (int i = 0; i < static_cast<int>(item.size()); i++)
        item[i].OnShow();

    for (int i = 0; i < static_cast<int>(bullet.size()); i++)
        bullet[i].OnShow();

    for (int i = 0; i < static_cast<int>(shotbullets.size()); i++)
        shotbullets[i].OnShow();
}
}
