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
    box.push_back(Box(100, 100));	//�[�J�@�ӽc�l
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

void CGameStateRun::OnMove()							// ���ʹC������
{
    //
    // �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
    //
    player1.SetMovingRight(1);
    player1.SetMovingDown(1);
    player1.SetMovingLeft(1);
    player1.SetMovingUP(1);

    for (int i = 0; i < static_cast<int>(box.size()); i++)
    {
        if (player1.GetY() + player1.GetHeight() > box.at(i).GetY() && player1.GetY() < box.at(i).GetY() + box.at(i).GetHeight() * 3)
        {
            //�k
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

            //��
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
            //�U
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

            //�W
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
//OnMove�n�g�����̫��
void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
    //
    // ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
    //     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
    //
    ShowInitProgress(33);
    ShowInitProgress(50);
    corner.LoadBitmap(IDB_CORNER);							// ���J�����ϧ�
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

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	if (!player1.isReloading()) {
		player1.SetReloading(true);
		int x = point.x-320;
		int y = point.y-240;
		double r = sqrt(x*x +y*y);
		shotbullets.push_back(shotBullet(int(x / r * 10), int(y / r * 10)));
	}
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	player1.SetReloading(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	player1.setFacingPosition(point.x, point.y);
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
    //  �K�W���W�Υk�U��������
    //
    corner.SetTopLeft(0, 0);
    corner.ShowBitmap();
    corner.SetTopLeft(SIZE_X - corner.Width(), SIZE_Y - corner.Height());
    corner.ShowBitmap();
}
}