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
}

void game_framework::UI::LoadBitMap()
{
}

void game_framework::UI::OnShow()
{
	ShowHealthBar();
}

void game_framework::UI::ShowHealthBar()
{
	CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
	CFont f, *fp;
	char buf[32];
	sprintf(buf, "%d", HP);
	f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
	fp = pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255, 255, 0));

	pDC->TextOut(5, 455, "HP:");
	pDC->TextOut(50, 455, buf);

	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

void game_framework::UI::TakePlayerInfo(int hp, int ammo)
{
	HP = hp;
	Ammo = ammo;
}

