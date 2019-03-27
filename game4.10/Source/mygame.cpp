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
    box.push_back(Box(100, 100));	//加入一個箱子
    item.push_back(items(400, 400));
    item.push_back(items(450, 450));
    bullet.push_back(Bullet(400, 100));
}

CGameStateRun::~CGameStateRun()
{
    //delete [] ball;
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
    //
    // 如果希望修改cursor的樣式，則將下面程式的commment取消即可
    //
    player1.SetMovingRight(1);
    player1.SetMovingDown(1);
    player1.SetMovingLeft(1);
    player1.SetMovingUP(1);

    for (int i = 0; i < static_cast<int>(box.size()); i++)
    {
        if (player1.GetY() + player1.GetHeight() > box.at(i).GetY() && player1.GetY() < box.at(i).GetY() + box.at(i).GetHeight() * 3)
        {
            //右
            if (player1.GetX() + player1.GetWidth() + 10 >= box.at(i).GetX() && !(player1.GetX() >= box.at(i).GetX() + box.at(i).GetWidth() * 3))
            {
                player1.SetMovingRight(0);
                map.SetMovingLeft(false);

                for (int j = 0; j < static_cast<int>(box.size()); j++)
                    box[j].SetMovingLeft(false);

                for (int j = 0; j < static_cast<int>(item.size()); j++)
                    item[j].SetMovingLeft(false);

                for (int j = 0; j < static_cast<int>(bullet.size()); j++)
                    bullet[j].SetMovingLeft(false);
            }

            //左
            if (player1.GetX() - 10 <= box.at(i).GetX() + box.at(i).GetWidth() * 3 && !(player1.GetX() + player1.GetWidth() < box.at(i).GetX()))
            {
                player1.SetMovingLeft(0);
                map.SetMovingRight(false);

                for (int j = 0; j < static_cast<int>(box.size()); j++)
                    box[j].SetMovingRight(false);

                for (int j = 0; j < static_cast<int>(item.size()); j++)
                    item[j].SetMovingRight(false);

                for (int j = 0; j < static_cast<int>(bullet.size()); j++)
                    bullet[j].SetMovingRight(false);
            }
        }

        if (player1.GetX() + player1.GetWidth() > box.at(i).GetX() && player1.GetX() < box.at(i).GetX() + box.at(i).GetWidth() * 3)
        {
            //下
            if (player1.GetY() + player1.GetHeight() + 10 > box.at(i).GetY() && !(player1.GetY() >= box.at(i).GetY() + box.at(i).GetHeight() * 3))
            {
                player1.SetMovingDown(0);
                map.SetMovingDown(false);

                for (int j = 0; j < static_cast<int>(box.size()); j++)
                    box[i].SetMovingDown(false);

                for (int j = 0; j < static_cast<int>(item.size()); j++)
                    item[i].SetMovingDown(false);

                for (int j = 0; j < static_cast<int>(bullet.size()); j++)
                    bullet[i].SetMovingDown(false);
            }

            //上
            if (player1.GetY() - 10 <= box.at(i).GetY() + box.at(i).GetHeight() * 3 && !(player1.GetY() + player1.GetHeight() < box.at(i).GetY()))
            {
                player1.SetMovingUP(0);
                map.SetMovingUP(false);

                for (int j = 0; j < static_cast<int>(box.size()); j++)
                    box[j].SetMovingUP(false);

                for (int j = 0; j < static_cast<int>(item.size()); j++)
                    item[j].SetMovingUP(false);

                for (int j = 0; j < static_cast<int>(bullet.size()); j++)
                    bullet[j].SetMovingUP(false);
            }
        }
    }

    map.OnMove();

    for(int i = 0 ; i < static_cast<int>(box.size()); i++)
        box.at(i).OnMove();

    for(int i = 0 ; i < static_cast<int>(item.size()); i++)
        item.at(i).OnMove();

    for (int i = 0; i < static_cast<int>(bullet.size()); i++)
        bullet.at(i).OnMove();

	for (int i = 0; i < static_cast<int>(shotbullets.size()); i++)
		shotbullets.at(i).OnMove();
}
//OnMove要寫未完最後修
void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
    //
    // 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
    //     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
    //
    ShowInitProgress(33);
    ShowInitProgress(50);
    corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
    map.LoadBitMap();

    for (int i = 0; i < static_cast<int>(box.size()); i++)
        box[i].LoadBitMap();

    for (int i = 0; i < static_cast<int>(item.size()); i++)
        item[i].LoadBitMap();

    for (int i = 0; i < static_cast<int>(bullet.size()); i++)
        bullet[i].LoadBitMap();

    player1.LoadBitMap();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT  = 0x41; // keyboard  [A]
    const char KEY_UP    = 0x57; // keyboard  [W]
    const char KEY_RIGHT = 0x44; // keyboard  [D]
    const char KEY_DOWN  = 0x53; // keyboard  [S]
    const char KEY_GET = 0x46;   // keyboard  [F]

    if (nChar == KEY_LEFT && player1.isCan_Left())
    {
        map.SetMovingRight(true);

        for (int i = 0; i < static_cast<int>(box.size()); i++)
            box[i].SetMovingRight(true);

        for (int i = 0; i < static_cast<int>(item.size()); i++)
            item[i].SetMovingRight(true);

        for (int i = 0; i < static_cast<int>(bullet.size()); i++)
            bullet[i].SetMovingRight(true);
    }

    if (nChar == KEY_RIGHT && player1.isCan_Right())
    {
        map.SetMovingLeft(true);

        for (int i = 0; i < static_cast<int>(box.size()); i++)
            box[i].SetMovingLeft(true);

        for (int i = 0; i < static_cast<int>(item.size()); i++)
            item[i].SetMovingLeft(true);

        for (int i = 0; i < static_cast<int>(bullet.size()); i++)
            bullet[i].SetMovingLeft(true);
    }

    if (nChar == KEY_UP && player1.isCan_UP())
    {
        map.SetMovingDown(true);

        for (int i = 0; i < static_cast<int>(box.size()); i++)
            box[i].SetMovingDown(true);

        for (int i = 0; i < static_cast<int>(item.size()); i++)
            item[i].SetMovingDown(true);

        for (int i = 0; i < static_cast<int>(bullet.size()); i++)
            bullet[i].SetMovingDown(true);
    }

    if (nChar == KEY_DOWN && player1.isCan_Down())
    {
        map.SetMovingUP(true);

        for (int i = 0; i < static_cast<int>(box.size()); i++)
            box[i].SetMovingUP(true);

        for (int i = 0; i < static_cast<int>(item.size()); i++)
            item[i].SetMovingUP(true);

        for (int i = 0; i < static_cast<int>(bullet.size()); i++)
            bullet[i].SetMovingUP(true);
    }

    if (nChar == KEY_GET)
    {
        player1.SetGetting(true);
    }
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
        map.SetMovingRight(false);

        for (int i = 0; i < static_cast<int>(box.size()); i++)
            box[i].SetMovingRight(false);

        for (int i = 0; i < static_cast<int>(item.size()); i++)
            item[i].SetMovingRight(false);

        for (int i = 0; i < static_cast<int>(bullet.size()); i++)
            bullet[i].SetMovingRight(false);
    }

    if (nChar == KEY_RIGHT)
    {
        map.SetMovingLeft(false);

        for (int i = 0; i < static_cast<int>(box.size()); i++)
            box[i].SetMovingLeft(false);

        for (int i = 0; i < static_cast<int>(item.size()); i++)
            item[i].SetMovingLeft(false);

        for (int i = 0; i < static_cast<int>(bullet.size()); i++)
            bullet[i].SetMovingLeft(false);
    }

    if (nChar == KEY_UP)
    {
        map.SetMovingDown(false);

        for (int i = 0; i < static_cast<int>(box.size()); i++)
            box[i].SetMovingDown(false);

        for (int i = 0; i < static_cast<int>(item.size()); i++)
            item[i].SetMovingDown(false);

        for (int i = 0; i < static_cast<int>(bullet.size()); i++)
            bullet[i].SetMovingDown(false);
    }

    if (nChar == KEY_DOWN)
    {
        map.SetMovingUP(false);

        for (int i = 0; i < static_cast<int>(box.size()); i++)
            box[i].SetMovingUP(false);

        for (int i = 0; i < static_cast<int>(item.size()); i++)
            item[i].SetMovingUP(false);

        for (int i = 0; i < static_cast<int>(bullet.size()); i++)
            bullet[i].SetMovingUP(false);
    }

    if (nChar == KEY_GET)
    {
        for (int i = 0; i < static_cast<int>(item.size()); i++)
            if (player1.isGetting() && (item.at(i).GetX() >= player1.GetX() && item.at(i).GetX() <= player1.GetX() + 30) && (item.at(i).GetY() >= player1.GetY() && item.at(i).GetY() <= player1.GetY() + 30))
            {
                item.at(i).SetAlive(false);
                player1.CatchItem(item.at(i));
            }

        for (int i = 0; i < static_cast<int>(bullet.size()); i++)
            if (player1.isGetting() && (bullet.at(i).GetX() >= player1.GetX() && bullet.at(i).GetX() <= player1.GetX() + 30) && (bullet.at(i).GetY() >= player1.GetY() && bullet.at(i).GetY() <= player1.GetY() + 30))
            {
                bullet.at(i).SetAlive(false);
                player1.setBullet(10);
            }

        player1.SetGetting(false);
    }
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	if (!player1.isReloading()) {
		player1.SetReloading(true);
		int x = point.x-320;
		int y = point.y-240;
		double r = sqrt(x*x +y*y);
		shotbullets.push_back(shotBullet(int(x / r * 10), int(y / r * 10)));
	}
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	player1.SetReloading(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	player1.setFacingPosition(point.x, point.y);
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
    player1.OnShow();

    for (int i = 0; i < static_cast<int>(box.size()); i++)
        box[i].OnShow();

    for (int i = 0; i < static_cast<int>(item.size()); i++)
        item[i].OnShow();

    for (int i = 0; i < static_cast<int>(bullet.size()); i++)
        bullet[i].OnShow();

	for (int i = 0; i < static_cast<int>(shotbullets.size()); i++)
		shotbullets[i].OnShow();
    //
    //  貼上左上及右下角落的圖
    //
    corner.SetTopLeft(0, 0);
    corner.ShowBitmap();
    corner.SetTopLeft(SIZE_X - corner.Width(), SIZE_Y - corner.Height());
    corner.ShowBitmap();
}
}