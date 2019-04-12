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
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame* g)
    : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
    ShowInitProgress(0);	
    //
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_ESC = 27;
    const char KEY_SPACE = ' ';

    if (nChar == KEY_SPACE)
        GotoGameState(GAME_STATE_RUN);						
    else if (nChar == KEY_ESC)								
        PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);	
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
    GotoGameState(GAME_STATE_RUN);		
}

void CGameStateInit::OnShow()
{
    CDC* pDC = CDDraw::GetBackCDC();			
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	
    fp = pDC->SelectObject(&f);					
    pDC->SetBkColor(RGB(0, 0, 0));
    pDC->SetTextColor(RGB(255, 255, 0));
    pDC->TextOut(120, 220, "Please click mouse or press SPACE to begin.");
    pDC->TextOut(5, 395, "Press Ctrl-F to switch in between window mode and full screen mode.");

    if (ENABLE_GAME_PAUSE)
        pDC->TextOut(5, 425, "Press Ctrl-Q to pause the Game.");

    pDC->TextOut(5, 455, "Press Alt-F4 or ESC to Quit.");
    pDC->SelectObject(fp);					
    CDDraw::ReleaseBackCDC();					
}

/////////////////////////////////////////////////////////////////////////////
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
    ShowInitProgress(66);	
    //
    //
    ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
    CDC* pDC = CDDraw::GetBackCDC();			
    CFont f, *fp;
    f.CreatePointFont(160, "Times New Roman");	
    fp = pDC->SelectObject(&f);					
    pDC->SetBkColor(RGB(0, 0, 0));
    pDC->SetTextColor(RGB(255, 255, 0));
    char str[80];								
    sprintf(str, "Game Over ! (%d)", counter / 30);
    pDC->TextOut(240, 210, str);
    pDC->SelectObject(fp);						
    CDDraw::ReleaseBackCDC();					
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame* g)
    : CGameState(g)  
{
    box.push_back(Box(100, 100));	
    box.push_back(Box(200, 200));
    item.push_back(items(400, 400, 1, (float)0.4));
    item.push_back(items(450, 450, 1, (float)0.4));

    for (int i = 0; i < 30; i++)
        bullet.push_back(Bullet(rand() % (1800 + 1), rand() % (1800 + 1)));
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

}

void CGameStateRun::OnMove()											
{
	SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));					
    for (int i = 1; i < 5; i++)
        player1.setMovingMode(i, 1);
	
	for (int i = 0; i < static_cast<int>(shotbullets.size()); i++) 
	{
		/*if (shotbullets.at(i).HitPlayer(&player1)) {
			shotbullets.erase(shotbullets.begin() + i);
		}*/
		for (int j = 0; j < static_cast<int>(box.size()); j++)
		{
			shotbullets.at(i).GetX();
			if (shotbullets.at(i).HitObstacle(&box.at(j))) {
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
    {
        if (player1.HitObstacle(&box.at(i), 1))
        {
            player1.setMovingMode(1, 0);
            map.setMovingMode(1, 0);
            ChangeMovingMode(1, 0);
        }

        if (player1.HitObstacle(&box.at(i), 2))
        {
            player1.setMovingMode(2, 0);
            map.setMovingMode(2, 0);
            ChangeMovingMode(2, 0);
        }

        if (player1.HitObstacle(&box.at(i), 3))
        {
            player1.setMovingMode(3, 0);
            map.setMovingMode(3, 0);
            ChangeMovingMode(3, 0);
        }

        if (player1.HitObstacle(&box.at(i), 4))
        {
            player1.setMovingMode(4, 0);
            map.setMovingMode(4, 0);
            ChangeMovingMode(4, 0);
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
	for (int i = 0; i < static_cast<int>(texture.size()); i++)
		texture.at(i).OnMove();
}

void CGameStateRun::OnInit()  							
{
    //
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
            if (player1.isGetting() && (item.at(i).GetX() >= player1.GetX() && item.at(i).GetX() <= player1.GetX() + 30) && (item.at(i).GetY() >= player1.GetY() && item.at(i).GetY() <= player1.GetY() + 30))
            {
                item.at(i).SetAlive(false);
                player1.CatchItem(item.at(i));
            }

        for (int i = 0; i < static_cast<int>(bullet.size()); i++)
            if (player1.isGetting() && (bullet.at(i).GetX() >= player1.GetX() && bullet.at(i).GetX() <= player1.GetX() + 30) && (bullet.at(i).GetY() >= player1.GetY() && bullet.at(i).GetY() <= player1.GetY() + 30))
            {
                bullet.at(i).SetAlive(false);
                bullet.erase(bullet.begin() + i);
                player1.setBullet(10);
            }

        player1.SetGetting(false);
    }
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  
{
    if (!player1.isReloading() && player1.getHasitemNum() != 0 && player1.getBullet() > 0)
    {
        player1.SetReloading(true);
        player1.setBullet(-1);
        int x = point.x - SIZE_X/2;
        int y = point.y - SIZE_Y / 2;
        double r = sqrt(x * x + y * y);
        shotbullets.push_back(shotBullet(int(x / r * 10), int(y / r * 10)));
    }
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	
{
    player1.SetReloading(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	
{	
	int x = point.x - SIZE_X / 2;
	int y = point.y - SIZE_Y / 2;
	double r = sqrt(x * x + y * y);
	player1.setFacingPosition(int(x / r * 10), int(y / r * 10));
	player1.setDirection();
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	
{
}

void CGameStateRun::OnShow()
{
    //
    //
    map.OnShow();
	player1.OnShow();
	for (int i = 0; i < static_cast<int>(texture.size()); i++)
		texture[i].OnShow();


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