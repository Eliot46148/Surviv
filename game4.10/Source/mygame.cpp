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
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame* g)
    : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
    ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
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
        GotoGameState(GAME_STATE_RUN);						// ������GAME_STATE_RUN
    else if (nChar == KEY_ESC)								// Demo �����C������k
        PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	// �����C��
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
    GotoGameState(GAME_STATE_RUN);		// ������GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{	
	logo.SetTopLeft(0, 0);
	logo.ShowBitmap();

	if (showTip) {
		CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->TextOut(200, 300, "Press LButton to Start!");
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
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
// �o��class���C�����������A(Game Over)
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
		CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
		CFont f, *fp;
		f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->TextOut(180, 300, "Press LButton to Restart!");
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
	}
}

void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_INIT);
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame* g)
    : CGameState(g)  //��l�Ƴ]�w
{
	firstlife = true;
	unsigned seed = (unsigned)time(NULL);
	srand(seed);
	//box.push_back(Box(100, 100));								// �[�J�c�l
	//box.push_back(Box(200, 200));								// �[�J�c�l
	int randomx, randomy;

	for (int i = 0; i < 15; i++)
	{
		randomx = rand() % (556 * 5);
		randomy = rand() % (556 * 5);
		item.push_back(items(randomx, randomy, i % 3 + 1, (float)0.4));
	}

	item.push_back(items(400, 400, 1, (float)0.4));				// �[�J��j
	item.push_back(items(450, 400, 2, (float)0.4));				// �[�J���j
	item.push_back(items(500, 400, 3, (float)0.4));				// �[�J�żu�j
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

void CGameStateRun::OnMove()											// ���ʹC������
{
    SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));					// ���г]�w

	ui.TakePlayerInfo(player1.GetHP(), player1.GetAmmo(), enemy.size(), player1.GetHasItemID(), player1.GetHoldingItem());				// UI�������a��T

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

        //�U���n��
        if (enemy.at(i).isActing())
        {
            if (enemy.at(i).hasbullet() != 0 && enemy.at(i).rrdelay < 0 )
            {
				enemy.at(i).rrdelay = enemy.at(i).Recoil_delay;
                int ID = enemy.at(i).catchitemID();
                double dx = player1.GetHitpointX() - enemy.at(i).GetX(), dy = player1.GetHitpointY() - enemy.at(i).GetY();
                double r = sqrt(dx * dx + dy * dy);
                const int distance = 100;			// �l�u�o�g�ɶZ���ۨ����Z��
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
        /* �l�u�I����ɷ|���� */
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

    ////////////////  OnMove�϶�  ////////////////////////////////////////////////////////////////////////////////////
    player1.OnMove();
    camera.OnMove();

    for (unsigned int i = 0; i < enemy.size(); i++)
        enemy.at(i).OnMove();

    for (unsigned int i = 0; i < shotbullets.size(); i++)
        shotbullets.at(i).OnMove();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////  �ʧ@�B�z    /////////////////////////////////////////////////////////////////////////////////////

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

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
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

    
    /////////// camera�����a�Ϫ����} ////////////////
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

    //////////// ���� //////////////////////////////////////
    if (nChar == KEY_LEFT)           // ��
    {
        camera.setMovingMode(4, 1);
        player1.setMovingMode(3, 1);
    }

    if (nChar == KEY_RIGHT)          // �k
    {
        camera.setMovingMode(3, 1);
        player1.setMovingMode(4, 1);
    }

    if (nChar == KEY_UP)             // �W
    {
        camera.setMovingMode(2, 1);
        player1.setMovingMode(1, 1);
    }

    if (nChar == KEY_DOWN)           // �U
    {
        camera.setMovingMode(1, 1);
        player1.setMovingMode(2, 1);
    }

    /////////////////////////////////////////////////////////

    /////////    �ʧ@         ///////////////////////////////
    if (nChar == KEY_GET)
    {
        player1.SetGetting(true);
    }

    if (nChar == KEY_RTBLOOD)
    {
		player1.returnBlood();
    }

    /////////////////////////////////////////////////////////

    //////////     �����Z��       ///////////////////////////////////////
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

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
    player1.setActing(true);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
    player1.setActing(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
    int x = point.x - (SIZE_X / 2);
    int y = point.y - (SIZE_Y / 2);
    double r = sqrt(x * x + y * y);
    player1.setFacingPosition(x / r * 10, y / r * 10);
    player1.setDirection();
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
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
    //  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
    //        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
    //        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
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
