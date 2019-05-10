#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <string>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "BasicObject.h"
#include "shotBullet.h"
#include "UI.h"

game_framework::UI::UI()
{
	HP = 100;
	Ammo = 0;
	Enemy_Num = 0;
	HealthStatus = 10;
}

void game_framework::UI::LoadBitMap()
{
	HealthBar[0].LoadBitmap(IDB_HealthBar11);
	HealthBar[1].LoadBitmap(IDB_HealthBar10);
	HealthBar[2].LoadBitmap(IDB_HealthBar9);
	HealthBar[3].LoadBitmap(IDB_HealthBar8);
	HealthBar[4].LoadBitmap(IDB_HealthBar7);
	HealthBar[5].LoadBitmap(IDB_HealthBar6);
	HealthBar[6].LoadBitmap(IDB_HealthBar5);
	HealthBar[7].LoadBitmap(IDB_HealthBar4);
	HealthBar[8].LoadBitmap(IDB_HealthBar3);
	HealthBar[9].LoadBitmap(IDB_HealthBar2);
	HealthBar[10].LoadBitmap(IDB_HealthBar1);
	Ammo_img.LoadBitmap(IDB_BULLET_IMG,RGB(255,255,255));
}

void game_framework::UI::OnShow()
{
	ShowHealthBar();
	ShowInfo();
}

void game_framework::UI::ShowHealthBar()
{
	HealthBar[HealthStatus].SetTopLeft(195, 430);
	HealthBar[HealthStatus].ShowBitmap();

	CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
	CFont f, *fp;
	char buf[32];

	///////// 生命值 ///////////////////////////////////////////////////////////////////
	f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
	fp = pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255, 255, 255));
	sprintf(buf, "%d", HP);
	pDC->TextOut(195, 430, "HP:");
	pDC->TextOut(240, 430, buf);
	pDC->TextOut(290, 430, "/ 100");
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	//////////////////////////////////////////////////////////////////////////////////////
}

void game_framework::UI::ShowInfo()
{
	CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
	CFont f, *fp;
	char buf[32];

	f.CreatePointFont(240, "Times New Roman");	// 產生 font f; 160表示16 point的字
	fp = pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkMode(TRANSPARENT);

	pDC->SetTextColor(RGB(255, 255, 255));
	sprintf(buf, "%d", Ammo);
	pDC->TextOut(560, 428, buf);
	
	pDC->SetTextColor(RGB(255, 0, 0));
	sprintf(buf, "%d", Enemy_Num);
	pDC->TextOut(450, 0, "Enemies:");
	pDC->TextOut(600, 2, buf);

	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC\

	Ammo_img.SetTopLeft(600, 430);
	Ammo_img.ShowBitmap(0.1);
}

void game_framework::UI::TakePlayerInfo(int hp, int ammo, int enemy_num)
{
	HP = hp;
	Ammo = ammo;
	Enemy_Num = enemy_num;
	SetHealthStatus();
}

void game_framework::UI::SetHealthStatus()
{
	HealthStatus = int((double)HP / 100 * 10);
}

