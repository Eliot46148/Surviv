#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <string>
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
	logo.LoadBitmap(IDB_LOGO);
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
	logo.SetTopLeft(0, 0);
	logo.ShowBitmap();

	if (showTip) {
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->TextOut(200, 300, "Press LButton to Start!");
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
}

void CGameStateInit::OnMove()
{
	
	if (delay >= 15) {
		delay = 0;
		showTip = !showTip;
	}
	else
		delay++;
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
	if (delay >= 15) {
		delay = 0;
		showTip = !showTip;
	}
	else
		delay++;
}

void CGameStateOver::OnBeginState()
{
}

void CGameStateOver::OnInit()
{	
	logo[0].LoadBitmap(IDB_WIN);
	logo[1].LoadBitmap(IDB_LOSE);
    ShowInitProgress(66);	
    ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	int result;
	if (isWin)
		result = 0;
	else
		result = 1;
	logo[result].SetTopLeft(0, 0);
	logo[result].ShowBitmap();
	if (showTip) {
		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->TextOut(180, 300, "Press LButton to Restart!");
		pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	}
}

void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_INIT);
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame* g)
    : CGameState(g)  //初始化設定
{
	firstlife = true;
	unsigned seed = (unsigned)time(NULL);
	srand(seed);
	//box.push_back(Box(100, 100));								// 加入箱子
	//box.push_back(Box(200, 200));								// 加入箱子
	int randomx, randomy;

	for (int i = 0; i < 15; i++)
	{
		randomx = rand() % (556 * 5);
		randomy = rand() % (556 * 5);
		item.push_back(items(randomx, randomy, i % 3 + 1, (float)0.4));
	}

	item.push_back(items(400, 400, 1, (float)0.4));				// 加入手槍
	item.push_back(items(450, 400, 2, (float)0.4));				// 加入機槍
	item.push_back(items(500, 400, 3, (float)0.4));				// 加入霰彈槍
	enemy.push_back(Enemy(100, 100, 1));

	for (int i = 0; i < 7; i++)
	{
		randomx = rand() % (556 * 5);
		randomy = rand() % (556 * 5);
		enemy.push_back(Enemy(randomx, randomy, randomx % 3 + 1));
	}

	for (int i = 0; i < 70; i++)
		bullet.push_back(Bullet(rand() % (556 * 5 + 1), rand() % (556 * 5 + 1)));
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{	
	if (firstlife)
		firstlife = false;
	else {
		player1.Retry();
		camera.Retry();
		shotbullets.clear();
	}
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

	ui.TakePlayerInfo(player1.GetHP(), player1.GetAmmo(), enemy.size(), player1.GetHasItemID(), player1.GetHoldingItem());				// UI接收玩家資訊

    for (int i = 0; i < static_cast<int>(enemy.size()); i++)
    {
		enemy.at(i).rrdelay += enemy.at(i).rrdelay < 0 ? 0 : -1;
        enemy.at(i).ClearBBIPvector();

        if (abs(player1.GetHitpointX() - enemy.at(i).GetX()) < SIZE_X / 2 && abs(player1.GetHitpointY() - enemy.at(i).GetY()) < SIZE_Y / 2)
            enemy.at(i).setnearperson(&player1);

        for (int j = 0; j < static_cast<int>(item.size()); j++)
            if (abs(item.at(j).GetX() - enemy.at(i).GetX()) < SIZE_X / 2 && abs(item.at(j).GetY() - enemy.at(i).GetY()) < SIZE_Y / 2)
                enemy.at(i).SetNearItem(&item.at(j));

        for (int j = 0; j < static_cast<int>(bullet.size()); j++)
            if (abs(bullet.at(j).GetX() - enemy.at(i).GetX()) < SIZE_X / 2 && abs(bullet.at(j).GetY() - enemy.at(i).GetY()) < SIZE_Y / 2)
                enemy.at(i).SetNearBullet(&bullet.at(j));

        enemy.at(i).chouseMode();

        //下面要修
        if (enemy.at(i).isActing())
        {
            if (enemy.at(i).hasbullet() != 0 && enemy.at(i).rrdelay < 0 )
            {
				enemy.at(i).rrdelay = enemy.at(i).Recoil_delay;
                int ID = enemy.at(i).catchitemID();
                double dx = player1.GetHitpointX() - enemy.at(i).GetX(), dy = player1.GetHitpointY() - enemy.at(i).GetY();
                double r = sqrt(dx * dx + dy * dy);
                const int distance = 100;			// 子彈發射時距離自身的距離
                double x = (dx / r) * distance, y = (dy / r) * distance;

                switch (ID)
                {
                    case 1:
                    case 2:
                        shotbullets.push_back(shotBullet((int)x, (int)y, enemy.at(i).GetX(), enemy.at(i).GetY(), camera.GetCameraX(), camera.GetCameraY(), i));
                        break;

                    case 3:
                        int degree = 15, temp = degree;
                        shotbullets.push_back(shotBullet((int)x, (int)y, enemy.at(i).GetX(), enemy.at(i).GetY(), camera.GetCameraX(), camera.GetCameraY(), i));
                        shotbullets.push_back(shotBullet(int(x * cos(temp * M_PI / 180) - y * sin(temp * M_PI / 180)), int(x * sin(temp * M_PI / 180) + y * cos(temp * M_PI / 180)), enemy.at(i).GetX(), enemy.at(i).GetY(), camera.GetCameraX(), camera.GetCameraY(), i));
                        temp = degree * 2;
                        shotbullets.push_back(shotBullet(int(x * cos(temp * M_PI / 180) - y * sin(temp * M_PI / 180)), int(x * sin(temp * M_PI / 180) + y * cos(temp * M_PI / 180)), enemy.at(i).GetX(), enemy.at(i).GetY(), camera.GetCameraX(), camera.GetCameraY(), i));
                        temp = degree * -1;
                        shotbullets.push_back(shotBullet(int(x * cos(temp * M_PI / 180) - y * sin(temp * M_PI / 180)), int(x * sin(temp * M_PI / 180) + y * cos(temp * M_PI / 180)), enemy.at(i).GetX(), enemy.at(i).GetY(), camera.GetCameraX(), camera.GetCameraY(), i));
                        temp = degree * -2;
                        shotbullets.push_back(shotBullet(int(x * cos(temp * M_PI / 180) - y * sin(temp * M_PI / 180)), int(x * sin(temp * M_PI / 180) + y * cos(temp * M_PI / 180)), enemy.at(i).GetX(), enemy.at(i).GetY(), camera.GetCameraX(), camera.GetCameraY(), i));
                        break;
                }
            }
        }

        for (int j = 0; j < static_cast<int>(item.size()); j++)
            if ((item.at(j).GetX() >= enemy.at(i).GetX()) && (item.at(j).GetX() <= enemy.at(i).GetX() + enemy.at(i).GetWidth()) && (item.at(j).GetY() >= enemy.at(i).GetY()) && (item.at(j).GetY() <= enemy.at(i).GetY() + enemy.at(i).GetHeight()) && (enemy.at(i).hasItom() < 2))
            {
                enemy.at(i).CatchItem(item.at(j));
				switch (item.at(j).getID()) {
				case 1:
					enemy.at(i).Recoil_delay = 20;
					break;
				case 2:
					enemy.at(i).Recoil_delay = 5;
					break;
				case 3:
					enemy.at(i).Recoil_delay = 60;
					break;
				}
				item.erase(item.begin() + j);

            }

        for (int j = 0; j < static_cast<int>(bullet.size()); j++)
            if ((bullet.at(j).GetX() >= enemy.at(i).GetX() && bullet.at(j).GetX() <= enemy.at(i).GetX() + enemy.at(i).GetWidth()) && (bullet.at(j).GetY() >= enemy.at(i).GetY() && bullet.at(j).GetY() <= enemy.at(i).GetY() + enemy.at(i).GetHeight()) && enemy.at(i).hasbullet() <= 300 )
            {
                enemy.at(i).setbullt(30);
                bullet.erase(bullet.begin() + j);
            }
    }

    for (int i = 0; i < static_cast<int>(shotbullets.size()); i++)
    {
        /* 子彈碰到邊界會消失 */
        if (shotbullets.at(i).GetX() >= SIZE_MAP + 10 || shotbullets.at(i).GetX() <= 10 || shotbullets.at(i).GetY() >= SIZE_MAP + 10 || shotbullets.at(i).GetY() <= 10)
        {
            shotbullets.erase(shotbullets.begin() + i);
            continue;
        }

		if (static_cast<int>(shotbullets.size()) != i && shotbullets.at(i).HitPlayer(&player1) && shotbullets.at(i).getshooter() != -1)
		{
			player1.getDemage(shotbullets.at(i).ShowDamage());
			shotbullets.erase(shotbullets.begin() + i);
			if (player1.GetHP() <= 0) {
				isWin = false;
				GotoGameState(GAME_STATE_OVER);
			}

		}



        for (int j = 0; j < static_cast<int>(enemy.size()); j++)
            if (static_cast<int>(shotbullets.size()) != i && shotbullets.at(i).HitPlayer(&enemy.at(j))&& shotbullets.at(i).getshooter()!=j)
            {
                enemy.at(j).GetDamage(shotbullets.at(i).ShowDamage());
                shotbullets.erase(shotbullets.begin() + i);

                if (enemy.at(j).GetHP() <= 0)
                {
                    texture.push_back(Texture(enemy.at(j).GetX(), enemy.at(j).GetY(), 2));

                    for (unsigned int i = 0; i < texture.size(); i++)
                        camera.AddObjects(&texture.at(i));

                    enemy.erase(enemy.begin() + j);
                }

                continue;
            }

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

                    for (unsigned int i = 0; i < texture.size(); i++)
                        camera.AddObjects(&texture.at(i));

                    box.erase(box.begin() + j);
                }
            }
        }
    }

    ////////////////  OnMove區塊  ////////////////////////////////////////////////////////////////////////////////////
    player1.OnMove();
    camera.OnMove();

    for (unsigned int i = 0; i < enemy.size(); i++)
        enemy.at(i).OnMove();

    for (unsigned int i = 0; i < shotbullets.size(); i++)
        shotbullets.at(i).OnMove();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////  動作處理    /////////////////////////////////////////////////////////////////////////////////////

    if (player1.isActing())
    {
        if (!player1.isReloading() && !player1.Recoil() && player1.getBullet() > 0)
        {
            int ID = player1.getHoldingItemID();
            double x = player1.getFacingX() * 10, y = player1.getFacingY() * 10;
			int position_x = player1.GetHitpointX(), position_y = player1.GetHitpointY();
			int camera_x = camera.GetCameraX(), camera_y = camera.GetCameraY();

            switch (ID)
            {
                case 1:
                case 2:
                    shotbullets.push_back(shotBullet((int)x, (int)y, position_x, position_y, camera_x, camera_y, -1));
					player1.setBullet(-1);
                    break;

                case 3:
                    int degree = 10, temp = degree;
                    shotbullets.push_back(shotBullet((int)x, (int)y, position_x, position_y, camera_x, camera_y, -1));
                    shotbullets.push_back(shotBullet(int(x * cos(temp * M_PI / 180) - y * sin(temp * M_PI / 180)), int(x * sin(temp * M_PI / 180) + y * cos(temp * M_PI / 180)), position_x, position_y, camera_x, camera_y, -1));
                    temp = degree * 2;
                    shotbullets.push_back(shotBullet(int(x * cos(temp * M_PI / 180) - y * sin(temp * M_PI / 180)), int(x * sin(temp * M_PI / 180) + y * cos(temp * M_PI / 180)), position_x, position_y, camera_x, camera_y, -1));
                    temp = degree * -1;
                    shotbullets.push_back(shotBullet(int(x * cos(temp * M_PI / 180) - y * sin(temp * M_PI / 180)), int(x * sin(temp * M_PI / 180) + y * cos(temp * M_PI / 180)), position_x, position_y, camera_x, camera_y, -1));
                    temp = degree * -2;
                    shotbullets.push_back(shotBullet(int(x * cos(temp * M_PI / 180) - y * sin(temp * M_PI / 180)), int(x * sin(temp * M_PI / 180) + y * cos(temp * M_PI / 180)), position_x, position_y, camera_x, camera_y, -1));
					player1.setBullet(-5);
					break;
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (static_cast<int>(enemy.size()) == 0) {
		isWin = true;
		GotoGameState(GAME_STATE_OVER);
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
    ShowInitProgress(33);
    ShowInitProgress(50);
    map.LoadBitMap();
	player1.LoadBitMap();
	ui.LoadBitMap();

    for (int i = 0; i < static_cast<int>(box.size()); i++)
        box[i].LoadBitMap();

    for (int i = 0; i < static_cast<int>(item.size()); i++)
        item[i].LoadBitMap();

    for (int i = 0; i < static_cast<int>(bullet.size()); i++)
        bullet[i].LoadBitMap();

    for (int i = 0; i < static_cast<int>(enemy.size()); i++)
        enemy[i].LoadBitMap();

    
    /////////// camera接收地圖物件位址 ////////////////
    camera.AddObjects(&map);
    camera.AddObjects(&player1);

    for (int i = 0; i < static_cast<int>(box.size()); i++)
        camera.AddObjects(&box.at(i));

    for (int i = 0; i < static_cast<int>(item.size()); i++)
        camera.AddObjects(&item.at(i));

    for (int i = 0; i < static_cast<int>(bullet.size()); i++)
        camera.AddObjects(&bullet.at(i));

    for (int i = 0; i < static_cast<int>(shotbullets.size()); i++)
        camera.AddObjects(&shotbullets.at(i));

    for (int i = 0; i < static_cast<int>(texture.size()); i++)
        camera.AddObjects(&texture.at(i));

    for (int i = 0; i < static_cast<int>(enemy.size()); i++)
        camera.AddObjects(&enemy.at(i));

    ////////////////////////////////////////////////////
	//dot.LoadBitmap(IDB_BALL);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT  = 0x41;		 // keyboard  [A]
    const char KEY_UP    = 0x57;		 // keyboard  [W]
    const char KEY_RIGHT = 0x44;		 // keyboard  [D]
    const char KEY_DOWN  = 0x53;		 // keyboard  [S]
    const char KEY_GET = 0x46;			 // keyboard  [F]
    const char KEY_RTBLOOD = 0x4F;		 // keyboard  [O]
	const char KEY_CHEAT = 0x43;		 // keyboard  [C]
    const char KEY_First = 0x31;		 // keyboard  [1]
    const char KEY_Second = 0x32;		 // keyboard  [2]
    const char KEY_Fist = 0x33;			 // keyboard  [3]
    //const char KEY_Grenade = 0x21;	 // keyboard  [4]

    //////////// 移動 //////////////////////////////////////
    if (nChar == KEY_LEFT)           // 左
    {
        camera.setMovingMode(4, 1);
        player1.setMovingMode(3, 1);
    }

    if (nChar == KEY_RIGHT)          // 右
    {
        camera.setMovingMode(3, 1);
        player1.setMovingMode(4, 1);
    }

    if (nChar == KEY_UP)             // 上
    {
        camera.setMovingMode(2, 1);
        player1.setMovingMode(1, 1);
    }

    if (nChar == KEY_DOWN)           // 下
    {
        camera.setMovingMode(1, 1);
        player1.setMovingMode(2, 1);
    }

    /////////////////////////////////////////////////////////

    /////////    動作         ///////////////////////////////
    if (nChar == KEY_GET)
    {
        player1.SetGetting(true);
    }

    if (nChar == KEY_RTBLOOD)
    {
		player1.returnBlood();
    }

    /////////////////////////////////////////////////////////

    //////////     切換武器       ///////////////////////////////////////
    if (nChar == KEY_First && player1.getHasitemNum() >= 1)
        player1.setHoldingItem(0);

    if (nChar == KEY_Second && player1.getHasitemNum() >= 2)
        player1.setHoldingItem(1);

    if (nChar == KEY_Fist)
        player1.setHoldingItem(2);

    /////////////////////////////////////////////////////////////////////

	if (nChar == KEY_CHEAT)          
	{
		Cheat();
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
        camera.setMovingMode(4, 0);
        player1.setMovingMode(3, 0);
    }

    if (nChar == KEY_RIGHT)
    {
        camera.setMovingMode(3, 0);
        player1.setMovingMode(4, 0);
    }

    if (nChar == KEY_UP)
    {
        camera.setMovingMode(2, 0);
        player1.setMovingMode(1, 0);
    }

    if (nChar == KEY_DOWN)
    {
        camera.setMovingMode(1, 0);
        player1.setMovingMode(2, 0);
    }

    if (nChar == KEY_GET)
    {
        for (int i = 0; i < static_cast<int>(item.size()); i++)
            if (player1.isGetting() && player1.getHasitemNum() < 2 && (item.at(i).GetX() >= player1.GetX() && item.at(i).GetX()  <= player1.GetX() + player1.GetWidth()) && (item.at(i).GetY() >= player1.GetY() && item.at(i).GetY()  <= player1.GetY() + player1.GetHeight()))
            {
                player1.CatchItem(item.at(i));
                item.erase(item.begin() + i);				
            }

        for (int i = 0; i < static_cast<int>(bullet.size()); i++)
            if (player1.isGetting() && (bullet.at(i).GetX() >= player1.GetX() && bullet.at(i).GetX() <= player1.GetX() + player1.GetWidth()) && (bullet.at(i).GetY() >= player1.GetY() && bullet.at(i).GetY() <= player1.GetY() + player1.GetHeight()))
            {
                bullet.erase(bullet.begin() + i);
                player1.setBullet(30);
            }

        player1.SetGetting(false);
    }
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
    player1.setActing(true);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
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

void CGameStateRun::Cheat()
{
	isWin = true;
	GotoGameState(GAME_STATE_OVER);
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
	
	ui.OnShow();

	//dot.SetTopLeft(SIZE_X / 2, SIZE_Y / 2);
	//dot.ShowBitmap();
}
}
