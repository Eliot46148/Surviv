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
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame* g)
    : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
    ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
    //
    // ���J��ƪ��a��
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
    // Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
    //
    CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
    fp = pDC->SelectObject(&f);					// ��� font f
    pDC->SetBkColor(RGB(0, 0, 0));
    pDC->SetTextColor(RGB(255, 255, 0));
    pDC->TextOut(120, 220, "Please click mouse or press SPACE to begin.");
    pDC->TextOut(5, 395, "Press Ctrl-F to switch in between window mode and full screen mode.");

    if (ENABLE_GAME_PAUSE)
        pDC->TextOut(5, 425, "Press Ctrl-Q to pause the Game.");

    pDC->TextOut(5, 455, "Press Alt-F4 or ESC to Quit.");
    pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
    CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
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
    ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
    //
    // �}�l���J������n�Ψ쪺���??
    //
    ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
    CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	// ���� font f; 160���16 point���r
    fp = pDC->SelectObject(&f);					// ��� font f
    pDC->SetBkColor(RGB(0, 0, 0));
    pDC->SetTextColor(RGB(255, 255, 0));
    char str[80];								// Demo �Ʀr��r�ꪺ�ഫ
    sprintf(str, "Game Over ! (%d)", counter / 30);
    pDC->TextOut(240, 210, str);
    pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
    CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame* g)
    : CGameState(g)  //��l�Ƴ]�w
{
    box.push_back(Box(100, 100));								// �[�J�c�l
    // box.push_back(Box(200, 200));								// �[�J�c�l
    item.push_back(items(400, 400, 1, (float)0.4));				// �[�J��j
    item.push_back(items(450, 400, 2, (float)0.4));				// �[�J���j
	item.push_back(items(500, 400, 3, (float)0.4));				// �[�J�żu�j
    enemy.push_back(Enemy(520, 240, 1));
    enemy.push_back(Enemy(490, 150, 2));
    enemy.push_back(Enemy(400, 150, 3));

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

void CGameStateRun::OnMove()											// ���ʹC������
{
   
	SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));					// ���г]�w
	bool isshow;

	//for (int i = 1; i < 5; i++)
		//player1.setMovingMode(i, 1);

	for (int i = 0; i < static_cast<int>(enemy.size()); i++)
	{
		if (enemy.at(i).moveDelay >= 60)
			enemy.at(i).moveDelay = 0;
		if (enemy.at(i).moveDelay <15)
		{
			enemy.at(i).setMovingMode(1, 1);
			enemy.at(i).setMovingMode(2, 0);
			enemy.at(i).setMovingMode(3, 0);
			enemy.at(i).setMovingMode(4, 0);
			enemy.at(i).moveDelay++;
		}
		else if (enemy.at(i).moveDelay < 30)
		{
			enemy.at(i).setMovingMode(1, 0);
			enemy.at(i).setMovingMode(2, 0);
			enemy.at(i).setMovingMode(3, 1);
			enemy.at(i).setMovingMode(4, 0);
			enemy.at(i).moveDelay++;
		}
		else if (enemy.at(i).moveDelay < 45)
		{
			enemy.at(i).setMovingMode(1, 0);
			enemy.at(i).setMovingMode(2, 1);
			enemy.at(i).setMovingMode(3, 0);
			enemy.at(i).setMovingMode(4, 0);
			enemy.at(i).moveDelay++;
		}
		else if (enemy.at(i).moveDelay < 60)
		{
			enemy.at(i).setMovingMode(1, 0);
			enemy.at(i).setMovingMode(2, 0);
			enemy.at(i).setMovingMode(3, 0);
			enemy.at(i).setMovingMode(4, 1);
			enemy.at(i).moveDelay++;
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
					for(unsigned int i=0;i<texture.size();i++)
						camera.AddObjects(&texture.at(i));
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
						for (unsigned int i = 0; i < texture.size(); i++)
							camera.AddObjects(&texture.at(i));
						box.erase(box.begin() + j);
					}
				}
			}
	}

	/*for (int i = 0; i < static_cast<int>(box.size()); i++)
		for (int j = 1; j < 5; j++)
			if (player1.HitObstacle(&box.at(i), j))
			{
				player1.setMovingMode(j, 0);
				map.setMovingMode(j, 0);
				ChangeMovingMode(j, 0);
			}*/

	////////////////  OnMove�϶�  ////////////////////////////////////////////////////////////////////////////////////
	player1.OnMove();
	camera.OnMove();
	for (unsigned int i = 0; i < enemy.size(); i++)
		enemy.at(i).OnMove();
	for (unsigned int i = 0; i < shotbullets.size(); i++)
		shotbullets.at(i).OnMove();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////  �ʧ@�B�z    /////////////////////////////////////////////////////////////////////////////////////
	if (player1.isActing()){
		if (!player1.isReloading() && !player1.Recoil() && player1.getBullet() > 0)
		{	
			int ID = player1.getHoldingItemID();
			int x = (int)player1.getFacingX(), y = (int)player1.getFacingY();
			switch (ID) {
			case 1:
			case 2:
				shotbullets.push_back(shotBullet((int)player1.getFacingX(), (int)player1.getFacingY()));
				break;
			case 3:
				int degree = 10, temp = degree;
				shotbullets.push_back(shotBullet((int)player1.getFacingX(), (int)player1.getFacingY()));
				shotbullets.push_back(shotBullet(int(x*cos(temp*M_PI / 180) - y * sin(temp*M_PI / 180)), int(x*sin(temp*M_PI / 180) + y * cos(temp*M_PI / 180))));
				temp = degree * 2;
				shotbullets.push_back(shotBullet(int(x*cos(temp*M_PI / 180) - y * sin(temp*M_PI / 180)), int(x*sin(temp*M_PI / 180) + y * cos(temp*M_PI / 180))));
				temp = degree * -1;
				shotbullets.push_back(shotBullet(int(x*cos(temp*M_PI / 180) - y * sin(temp*M_PI / 180)), int(x*sin(temp*M_PI / 180) + y * cos(temp*M_PI / 180))));
				temp = degree * -2;
				shotbullets.push_back(shotBullet(int(x*cos(temp*M_PI / 180) - y * sin(temp*M_PI / 180)), int(x*sin(temp*M_PI / 180) + y * cos(temp*M_PI / 180))));
				break;
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
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
    /////////// camera�����a�Ϫ����} ////////////////
    camera.AddObjects(&map);

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

    if (nChar == KEY_LEFT)
    {
        camera.setMovingMode(4, 1);
        player1.setMovingMode(3, 1);
    }

    if (nChar == KEY_RIGHT)
    {
        camera.setMovingMode(3, 1);
        player1.setMovingMode(4, 1);
    }

    if (nChar == KEY_UP)
    {
        camera.setMovingMode(2, 1);
        player1.setMovingMode(1, 1);
    }

    if (nChar == KEY_DOWN)
    {
        camera.setMovingMode(1, 1);
        player1.setMovingMode(2, 1);
    }

    if (nChar == KEY_GET)
    {
        player1.SetGetting(true);
    }

    if (nChar == KEY_RTBLOOD)
    {
        enemy.at(0).returnBlood();
    }

    //////////     �����Z��       ///////////////////////////////////////
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
                //item.at(i).SetAlive(false);
                player1.CatchItem(item.at(i));
                item.erase(item.begin() + i);
            }

        for (int i = 0; i < static_cast<int>(bullet.size()); i++)
            if (player1.isGetting() && (bullet.at(i).GetX() >= player1.GetX() && bullet.at(i).GetX() <= player1.GetX() + player1.GetWidth()) && (bullet.at(i).GetY() >= player1.GetY() && bullet.at(i).GetY() <= player1.GetY() + player1.GetHeight()))
            {
                //bullet.at(i).SetAlive(false);
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
}
}
