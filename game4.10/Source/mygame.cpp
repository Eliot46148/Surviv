#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <string>
#include <ddraw.h>
#include <random>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "BasicObject.h"
#include "persona.h"
#include "Blood.h"


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
    if (!isMusicLoaded) {
        CAudio::Instance()->Load(AUDIO_TITLE, "sounds\\title.mp3");
        isMusicLoaded = true;
    }

    CAudio::Instance()->Play(AUDIO_TITLE, true);
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

    CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
    fp = pDC->SelectObject(&f);					// 選用 font f
    pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextColor(RGB(255, 255, 255));
	pDC->TextOut(40, 240, "操作方法：");
	pDC->TextOut(40, 270, "使用WASD鍵移動");
	pDC->TextOut(40, 300, "F鍵拾取物品");
	pDC->TextOut(40, 330, "R鍵重新裝填子彈");
	pDC->TextOut(40, 360, "滑鼠移動控制準心瞄準");
	pDC->TextOut(40, 390, "滑鼠左鍵射擊或使用道具");
	pDC->TextOut(40, 420, "數字鍵1 2 切換武器/道具");

	pDC->TextOut(330, 240, "密技：");
	pDC->TextOut(330, 270, "O鍵回復生命值");
	pDC->TextOut(330, 300, "T鍵進入無敵模式(不會損血)");
	pDC->TextOut(330, 330, "C鍵直接勝利");

	pDC->SetTextColor(RGB(255, 255, 0));
    if (showTip)
    {
        pDC->TextOut(330, 390, "Press LButton to Start!");
    }

    pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
    CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

void CGameStateInit::OnMove()
{
    if (delay >= 15)
    {
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
    if (delay >= 15)
    {
        delay = 0;
        showTip = !showTip;
        is_delayed = true;
    }
    else
        delay++;
}

void CGameStateOver::OnBeginState()
{
    is_delayed = false;
    CAudio::Instance()->Pause();
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

    if (showTip)
    {
        CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
        CFont f, *fp;
        f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
        fp = pDC->SelectObject(&f);					// 選用 font f
        pDC->SetBkMode(TRANSPARENT);
        pDC->SetTextColor(RGB(255, 255, 255));
        pDC->TextOut(210, 300, "Press LButton to Restart!");
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
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
    player1.Retry();
    camera.Retry();
    shotbullets.clear();
    enemy.clear();
    box.clear();
    item.clear();
    bullet.clear();
    texture.clear();
    blood.clear();
    ui.Clear();
    firstlife = true;
    unsigned seed = (unsigned)time(NULL);
    srand(seed);
    int randomx, randomy;
    int ls[] = { 1, 2, 4 };

    for (int i = 0; i < 15; i++)
    {
        randomx = rand() % (556 * 5);
        randomy = rand() % (556 * 5);
        item.push_back(items(randomx, randomy, ls[i % 3], (float)0.4));
    }

    item.push_back(items(400, 400, 1, (float)0.4));				// 加入手槍
    item.push_back(items(450, 400, 2, (float)0.4));				// 加入機槍
    item.push_back(items(500, 400, 3, (float)0.4));				// 加入霰彈槍
    item.push_back(items(550, 400, 4, (float)0.4));

    for (int i = 0; i < 8; i++)
    {
        randomx = rand() % (556 * 5);
        randomy = rand() % (556 * 5);
        enemy.push_back(Enemy(randomx, randomy, randomx % 3 + 1));
    }

    for (int i = 0; i < 10; i++)
    {
        randomx = rand() % (556 * 5);
        randomy = rand() % (556 * 5);
        box.push_back(Box(randomx, randomy));								// 加入箱子

        if (Hascover(&box.at(i)))
        {
            box.erase(box.begin() + i);
            i--;
        }
    }

    for (int i = 0; i < 75; i++)
        bullet.push_back(Bullet(rand() % (556 * 5 + 1), rand() % (556 * 5 + 1)));

    for (int i = 0; i < static_cast<int>(enemy.size()); i++)
        enemy[i].LoadBitMap();

    for (int i = 0; i < static_cast<int>(box.size()); i++)
        box[i].LoadBitMap();

    for (int i = 0; i < static_cast<int>(item.size()); i++)
        item[i].LoadBitMap();

    for (int i = 0; i < static_cast<int>(bullet.size()); i++)
        bullet[i].LoadBitMap();

    CAudio::Instance()->Stop(AUDIO_TITLE);
	CAudio::Instance()->Play(AUDIO_BATTLE,true);
}

bool CGameStateRun::Hascover(Box* box)
{
    if (player1.HitObstacle(box, 0))return false;

    for (int i = 0; i < static_cast<int>(enemy.size()); i++)
    {
        if(enemy.at(i).tutchbox(box, 0))
            return false;
    }

    return 0;
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
    random_device rndseed;
    srand(rndseed());
    int rnd;
    ui.TakePlayerInfo(player1.GetHP(), player1.GetAmmo(), player1.GetMegazine(), enemy.size(), player1.GetHasItemID(), player1.GetHoldingItem(), player1.isReloading(), player1.GetBloodLock());				// UI接收玩家資訊

    for (int i = 0; i < static_cast<int>(box.size()); i++)
    {
        if (player1.HitObstacle(&box.at(i), 1))
        {
            camera.setMovingMode(2, 0);
            player1.setMovingMode(1, 0);
        }

        if (player1.HitObstacle(&box.at(i), 2))
        {
            camera.setMovingMode(1, 0);
            player1.setMovingMode(2, 0);
        }

        if (player1.HitObstacle(&box.at(i), 3))
        {
            camera.setMovingMode(4, 0);
            player1.setMovingMode(3, 0);
        }

        if (player1.HitObstacle(&box.at(i), 4))
        {
            camera.setMovingMode(3, 0);
            player1.setMovingMode(4, 0);
        }
    }

    if (player1.HitBorder(1))
    {
        camera.setMovingMode(2, 0);
        player1.setMovingMode(1, 0);
    }

    if (player1.HitBorder(2))
    {
        camera.setMovingMode(1, 0);
        player1.setMovingMode(2, 0);
    }

    if (player1.HitBorder(3))
    {
        camera.setMovingMode(4, 0);
        player1.setMovingMode(3, 0);
    }

    if (player1.HitBorder(4))
    {
        camera.setMovingMode(3, 0);
        player1.setMovingMode(4, 0);
    }

    ///////////////////角色在包紮時不能移動//////////////////////
    if (player1.isReloading() && player1.getHoldingItemID() == 4)
    {
        camera.setMovingMode(1, 0);
        camera.setMovingMode(2, 0);
        camera.setMovingMode(3, 0);
        camera.setMovingMode(4, 0);
        player1.setMovingMode(1, 0);
        player1.setMovingMode(2, 0);
        player1.setMovingMode(3, 0);
        player1.setMovingMode(4, 0);
    }

    for (int i = 0; i < static_cast<int>(enemy.size()); i++)
    {
        int shoutbox = -1;
        enemy.at(i).rrdelay += enemy.at(i).rrdelay < 0 ? 0 : -1;
        enemy.at(i).ClearBBIPvector();

        if (abs(player1.GetHitpointX() - enemy.at(i).GetX()) < SIZE_X / 2 && abs(player1.GetHitpointY() - enemy.at(i).GetY()) < SIZE_Y / 2)
            enemy.at(i).setnearperson(&player1);

        for (int j = 0; j < static_cast<int>(enemy.size()); j++)
            if ((abs(enemy.at(j).GetHitpointX() - enemy.at(i).GetX()) < SIZE_X / 2 && abs(enemy.at(j).GetHitpointY() - enemy.at(i).GetY()) < SIZE_Y / 2) && j != i)
                enemy.at(i).setnearperson(&enemy.at(j));

        for (int j = 0; j < static_cast<int>(item.size()); j++)
            if (abs(item.at(j).GetX() - enemy.at(i).GetX()) < SIZE_X / 2 && abs(item.at(j).GetY() - enemy.at(i).GetY()) < SIZE_Y / 2)
                enemy.at(i).SetNearItem(&item.at(j));

        for (int j = 0; j < static_cast<int>(bullet.size()); j++)
            if (abs(bullet.at(j).GetX() - enemy.at(i).GetX()) < SIZE_X / 2 && abs(bullet.at(j).GetY() - enemy.at(i).GetY()) < SIZE_Y / 2)
                enemy.at(i).SetNearBullet(&bullet.at(j));

        for (int j = 0; j < static_cast<int>(box.size()); j++)
            if (abs(box.at(j).GetX() - enemy.at(i).GetX()) < SIZE_X / 2 && abs(box.at(j).GetY() - enemy.at(i).GetY()) < SIZE_Y / 2)
                enemy.at(i).SetNearBox(&box.at(j));

        enemy.at(i).chouseMode();

        for (int j = 0; j < static_cast<int>(box.size()); j++)
            if (enemy.at(i).hitBox(&box.at(j)))
                shoutbox = j;

        if (enemy.at(i).isActing())
        {
            if (enemy.at(i).hasbullet() != 0 && enemy.at(i).rrdelay < 0 && enemy.at(i).hasItom() != 0)
            {
                enemy.at(i).rrdelay = enemy.at(i).Recoil_delay;
                int randomp, ID;
                double dx, dy, r, x, y;
                const int distance = 100;			// 子彈發射時距離自身的距離

                if (shoutbox == -1)
                {
                    randomp = rand() % enemy.at(i).rtNearPeople();
                    dx = enemy.at(i).nearPerson.at(randomp).GetHitpointX() - enemy.at(i).GetX();
                    dy = enemy.at(i).nearPerson.at(randomp).GetHitpointY() - enemy.at(i).GetY();
                }
                else
                {
                    dx = box.at(shoutbox).GetX() - enemy.at(i).GetX();
                    dy = box.at(shoutbox).GetY() - enemy.at(i).GetY();
                }

                ID = enemy.at(i).catchitemID();
                r = sqrt(dx * dx + dy * dy);
                x = (dx / r) * distance;
                y = (dy / r) * distance;

                switch (ID)
                {
                    case 1:
                        shotbullets.push_back(shotBullet((int)x, (int)y, enemy.at(i).GetX(), enemy.at(i).GetY(), camera.GetX(), camera.GetY(), i, 2));
                        break;

                    case 2:
                        rnd = rand() % 60 - 30;
                        shotbullets.push_back(shotBullet(int(x * cos(rnd * M_PI / 180) - y * sin(rnd * M_PI / 180)), int(x * sin(rnd * M_PI / 180) + y * cos(rnd * M_PI / 180)), enemy.at(i).GetX(), enemy.at(i).GetY(), camera.GetX(), camera.GetY(), i, 2));
                        break;

                    case 3:
                        int degree = 15, temp = degree;
                        shotbullets.push_back(shotBullet((int)x, (int)y, enemy.at(i).GetX(), enemy.at(i).GetY(), camera.GetX(), camera.GetY(), i, 2));
                        shotbullets.push_back(shotBullet(int(x * cos(temp * M_PI / 180) - y * sin(temp * M_PI / 180)), int(x * sin(temp * M_PI / 180) + y * cos(temp * M_PI / 180)), enemy.at(i).GetX(), enemy.at(i).GetY(), camera.GetX(), camera.GetY(), i, 2));
                        temp = degree * 2;
                        shotbullets.push_back(shotBullet(int(x * cos(temp * M_PI / 180) - y * sin(temp * M_PI / 180)), int(x * sin(temp * M_PI / 180) + y * cos(temp * M_PI / 180)), enemy.at(i).GetX(), enemy.at(i).GetY(), camera.GetX(), camera.GetY(), i, 2));
                        temp = degree * -1;
                        shotbullets.push_back(shotBullet(int(x * cos(temp * M_PI / 180) - y * sin(temp * M_PI / 180)), int(x * sin(temp * M_PI / 180) + y * cos(temp * M_PI / 180)), enemy.at(i).GetX(), enemy.at(i).GetY(), camera.GetX(), camera.GetY(), i, 2));
                        temp = degree * -2;
                        shotbullets.push_back(shotBullet(int(x * cos(temp * M_PI / 180) - y * sin(temp * M_PI / 180)), int(x * sin(temp * M_PI / 180) + y * cos(temp * M_PI / 180)), enemy.at(i).GetX(), enemy.at(i).GetY(), camera.GetX(), camera.GetY(), i, 2));
                        break;
                }
            }
        }

        for (int j = 0; j < static_cast<int>(item.size()); j++)
            if ((item.at(j).GetX() >= enemy.at(i).GetX()) && (item.at(j).GetX() <= enemy.at(i).GetX() + enemy.at(i).GetWidth()) && (item.at(j).GetY() >= enemy.at(i).GetY()) && (item.at(j).GetY() <= enemy.at(i).GetY() + enemy.at(i).GetHeight()) && (enemy.at(i).hasItom() < 2))
            {
                enemy.at(i).CatchItem(item.at(j));

                switch (item.at(j).getID())
                {
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
            blood.push_back(Blood(shotbullets.at(i).GetX(), shotbullets.at(i).GetY()));
            shotbullets.erase(shotbullets.begin() + i);

            if (player1.GetHP() <= 0)
            {
                isWin = false;
                GotoGameState(GAME_STATE_OVER);
            }

            continue;
        }

        for (int j = 0; j < static_cast<int>(enemy.size()); j++)
            if ((int)shotbullets.size() > i && (static_cast<int>(shotbullets.size()) != i && shotbullets.at(i).HitEnemy(&enemy.at(j)) && shotbullets.at(i).getshooter() != j))
            {
                enemy.at(j).GetDamage(shotbullets.at(i).ShowDamage());
                blood.push_back(Blood(shotbullets.at(i).GetX(), shotbullets.at(i).GetY()));
                shotbullets.erase(shotbullets.begin() + i);

                if (enemy.at(j).GetHP() <= 0)
                {
                    texture.push_back(Texture(enemy.at(j).GetX(), enemy.at(j).GetY(), 2));

                    for (int k = 0; k < enemy.at(j).sizeitom(); k++)
                    {
                        item.push_back(items(enemy.at(j).GetX() + 5 * k, enemy.at(j).GetY() + rand() % 3 * k, enemy.at(j).rtItom(k), (float)0.4));
                        item.at(item.size() - 1).LoadBitMap();
                    }

                    enemy.erase(enemy.begin() + j);
                }
            }

        for (int j = 0; j < static_cast<int>(box.size()); j++)
            if ((int)shotbullets.size() > i && shotbullets.at(i).HitObstacle(&box.at(j)) )
            {
                box.at(j).GetDamage(shotbullets.at(i).ShowDamage());
                shotbullets.erase(shotbullets.begin() + i);

                if (box.at(j).ShowHP() <= 0)
                {
                    texture.push_back(Texture(box.at(j).GetX(), box.at(j).GetY(), 1));
                    item.push_back(items(box.at(j).GetX(), box.at(j).GetY(), 3, (float)0.4));
                    item.at(item.size() - 1).LoadBitMap();
                    box.erase(box.begin() + j);
                }
            }
    }

    ////////////////  OnMove區塊  ////////////////////////////////////////////////////////////////////////////////////
    player1.OnMove();
    camera.OnMove();

    for (unsigned int i = 0; i < enemy.size(); i++)
        enemy.at(i).OnMove();

    for (unsigned int i = 0; i < shotbullets.size(); i++)
        shotbullets[i].OnMove();

    for (unsigned int i = 0; i < blood.size(); i++)
        blood[i].OnMove();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////  動作處理    /////////////////////////////////////////////////////////////////////////////////////

    if (player1.isActing())
    {
        if (!player1.isReloading() && !player1.Recoil())
        {
            int ID = player1.getHoldingItemID();
            double x = player1.getFacingX() * 10, y = player1.getFacingY() * 10;
            int position_x = player1.GetHitpointX(), position_y = player1.GetHitpointY();
            int camera_x = camera.GetX(), camera_y = camera.GetY();

            switch (ID)
            {
                case 1:
                    if (player1.GetMegazine() > 0)
                    {
                        shotbullets.push_back(shotBullet((int)x, (int)y, position_x, position_y, camera_x, camera_y, -1, 1));
                        CAudio::Instance()->Play(AUDIO_PISTOL, false);
                        player1.setMegazine(-1);
                    }

                    break;

                case 2:
                    if (player1.GetMegazine() > 0)
                    {
                        rnd = rand() % 30 - 15;
                        shotbullets.push_back(shotBullet(int(x * cos(rnd * M_PI / 180) - y * sin(rnd * M_PI / 180)), int(x * sin(rnd * M_PI / 180) + y * cos(rnd * M_PI / 180)), position_x, position_y, camera_x, camera_y, -1, 1));
                        player1.setMegazine(-1);
                    }

                    break;

                case 3:
                    if (player1.GetMegazine() >= 5)
                    {
                        int degree = 10, temp = degree;
                        shotbullets.push_back(shotBullet((int)x, (int)y, position_x, position_y, camera_x, camera_y, -1, 1));
                        shotbullets.push_back(shotBullet(int(x * cos(temp * M_PI / 180) - y * sin(temp * M_PI / 180)), int(x * sin(temp * M_PI / 180) + y * cos(temp * M_PI / 180)), position_x, position_y, camera_x, camera_y, -1, 1));
                        temp = degree * 2;
                        shotbullets.push_back(shotBullet(int(x * cos(temp * M_PI / 180) - y * sin(temp * M_PI / 180)), int(x * sin(temp * M_PI / 180) + y * cos(temp * M_PI / 180)), position_x, position_y, camera_x, camera_y, -1, 1));
                        temp = degree * -1;
                        shotbullets.push_back(shotBullet(int(x * cos(temp * M_PI / 180) - y * sin(temp * M_PI / 180)), int(x * sin(temp * M_PI / 180) + y * cos(temp * M_PI / 180)), position_x, position_y, camera_x, camera_y, -1, 1));
                        temp = degree * -2;
                        shotbullets.push_back(shotBullet(int(x * cos(temp * M_PI / 180) - y * sin(temp * M_PI / 180)), int(x * sin(temp * M_PI / 180) + y * cos(temp * M_PI / 180)), position_x, position_y, camera_x, camera_y, -1, 1));
                        CAudio::Instance()->Play(AUDIO_SHOTGUN, false);
                        player1.setMegazine(-5);
                    }

                    break;

                case 4:
                    player1.SetReloading(true);
                    break;
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////// Camera /////////////////////////////////////////////////////////////////////////////////////

    for (unsigned int i = 0; i < enemy.size(); i++)
        enemy.at(i).SetCamera(camera.GetX(), camera.GetY());

    for (unsigned int i = 0; i < blood.size(); i++)
        blood.at(i).SetCamera(camera.GetX(), camera.GetY());

    for (unsigned int i = 0; i < texture.size(); i++)
        texture.at(i).SetCamera(camera.GetX(), camera.GetY());

    for (unsigned int i = 0; i < item.size(); i++)
        item.at(i).SetCamera(camera.GetX(), camera.GetY());

    for (unsigned int i = 0; i < bullet.size(); i++)
        bullet.at(i).SetCamera(camera.GetX(), camera.GetY());

    for (unsigned int i = 0; i < shotbullets.size(); i++)
        shotbullets.at(i).SetCamera(camera.GetX(), camera.GetY());

    for (unsigned int i = 0; i < box.size(); i++)
        box.at(i).SetCamera(camera.GetX(), camera.GetY());

    map.SetCamera(camera.GetX(), camera.GetY());
    player1.SetCamera(camera.GetX(), camera.GetY());

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (static_cast<int>(enemy.size()) == 0)
    {
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
    CAudio::Instance()->Load(AUDIO_STEP, "sounds\\step.mp3");
    CAudio::Instance()->Load(AUDIO_PISTOL, "sounds\\pistol.mp3");
    CAudio::Instance()->Load(AUDIO_MACHINEGUN, "sounds\\machinegun.mp3");
    CAudio::Instance()->Load(AUDIO_SHOTGUN, "sounds\\shotgun.mp3");
    CAudio::Instance()->Load(AUDIO_BANDAGE, "sounds\\bandage.mp3");
	CAudio::Instance()->Load(AUDIO_BATTLE, "sounds\\battle.mp3");
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT  = 0x41;		 // keyboard  [A]
    const char KEY_UP    = 0x57;		 // keyboard  [W]
    const char KEY_RIGHT = 0x44;		 // keyboard  [D]
    const char KEY_DOWN  = 0x53;		 // keyboard  [S]
    const char KEY_GET   = 0x46;		 // keyboard  [F]
    const char KEY_Reload = 0x52;        // keyboard  [R]
    const char KEY_RTBLOOD = 0x4F;		 // keyboard  [O]
    const char KEY_BloodLock = 0x54;     // keyboard  [T]
    const char KEY_CHEAT = 0x43;		 // keyboard  [C]
    const char KEY_First = 0x31;		 // keyboard  [1]
    const char KEY_Second = 0x32;		 // keyboard  [2]
    const char KEY_Fist = 0x33;			 // keyboard  [3]
    const char KEY_Escape = 0x18;        // keyboard  [Esc]

    //////////// 移動 //////////////////////////////////////
    if ((nChar == KEY_LEFT || nChar == KEY_RIGHT || nChar == KEY_UP || nChar == KEY_DOWN) && !player1.isMoving()) {
        CAudio::Instance()->Play(AUDIO_STEP, true);;
    }

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

    if (!player1.isReloading())
    {
        /////////    動作         ///////////////////////////////
        if (nChar == KEY_GET)
        {
            player1.SetGetting(true);
        }

        if (nChar == KEY_Reload && player1.getHasitemNum() > 0 && player1.getHoldingItemID() != 4)
        {
            player1.SetReloading(true);
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
    }

    /////////////////////////////////////////////////////////////////////

    if (nChar == KEY_CHEAT)
    {
        Cheat();
    }

    if (nChar == KEY_BloodLock)
        player1.setBloodLock();
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

    if ((nChar == KEY_LEFT || nChar == KEY_RIGHT || nChar == KEY_UP || nChar == KEY_DOWN) && !player1.isMoving()) {
        CAudio::Instance()->Stop(AUDIO_STEP);
    }

    if (nChar == KEY_GET)
    {
        for (int i = 0; i < static_cast<int>(item.size()); i++)
            if (player1.isGetting() && (item.at(i).GetX() >= player1.GetX() && item.at(i).GetX()  <= player1.GetX() + player1.GetWidth()) && (item.at(i).GetY() >= player1.GetY() && item.at(i).GetY()  <= player1.GetY() + player1.GetHeight()))
            {
                if (player1.getHasitemNum() >= 2)
                {
                    item.push_back(items(player1.GetX(), player1.GetY(), player1.getHoldingItemID(), (float)0.4));
                    item.back().LoadBitMap();
                }

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

    if(player1.getHoldingItemID() == 2)
        CAudio::Instance()->Play(AUDIO_MACHINEGUN, true);

    if (player1.getHoldingItemID() == 4)
        CAudio::Instance()->Play(AUDIO_BANDAGE, false);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
    player1.setActing(false);
    CAudio::Instance()->Stop(AUDIO_MACHINEGUN);
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

    for (int i = 0; i < static_cast<int>(blood.size()); i++)
        blood.at(i).OnShow();

    for (int i = 0; i < static_cast<int>(bullet.size()); i++)
        bullet[i].OnShow();

    for (int i = 0; i < static_cast<int>(item.size()); i++)
        item[i].OnShow();

    for (int i = 0; i < static_cast<int>(enemy.size()); i++)
        enemy[i].OnShow();

    player1.OnShow();

    for (int i = 0; i < static_cast<int>(box.size()); i++)
        box[i].OnShow();

    for (int i = 0; i < static_cast<int>(shotbullets.size()); i++)
        shotbullets[i].OnShow();

    ui.OnShow();
}
}
