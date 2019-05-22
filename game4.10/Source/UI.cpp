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
	hasitemsID = nullptr;
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

	ItemUI[0][0].LoadBitmap(IDB_ItemUI1);
	ItemUI[0][1].LoadBitmap(IDB_ItemUI2);
	ItemUI[1][0].LoadBitmap(IDB_ItemUI1_2);
	ItemUI[1][1].LoadBitmap(IDB_ItemUI2_2);

	items_img[0].LoadBitmap(IDB_PISTOL1, RGB(0, 0, 0));
	items_img[1].LoadBitmap(IDB_MachineGun, RGB(0, 0, 0));
	items_img[2].LoadBitmap(IDB_ShotGun, RGB(0, 0, 0));

	bullet_img[0].LoadBitmap(IDB_BULLET);
	bullet_img[1].LoadBitmap(IDB_BULLET2);
	bullet_img[2].LoadBitmap(IDB_BULLET3);
}

void game_framework::UI::OnShow()
{
	ShowHealthBar();
	ShowInfo();
	ShowItems();
	ShowBullets();
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
	
	pDC->SetTextColor(RGB(255, 0, 0));
	sprintf(buf, "%d", Enemy_Num);
	pDC->TextOut(450, 0, "Enemies:");
	pDC->TextOut(600, 2, buf);

	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC

	//Ammo_img.SetTopLeft(600, 430);
	//Ammo_img.ShowBitmap(0.1);
}

void game_framework::UI::ShowItems()
{	
	//ItemUI[0].SetTopLeft(530, 275);
	//ItemUI[0].ShowBitmap(0.4);
	if (holdingitem == 0) {
		ItemUI[1][0].SetTopLeft(530, 340);
		ItemUI[1][0].ShowBitmap(0.4);
	}
	else {
		ItemUI[0][0].SetTopLeft(530, 340);
		ItemUI[0][0].ShowBitmap(0.4);
	}

	if (holdingitem == 1) {
		ItemUI[1][1].SetTopLeft(530, 405);
		ItemUI[1][1].ShowBitmap(0.4);
	}
	else {
		ItemUI[0][1].SetTopLeft(530, 405);
		ItemUI[0][1].ShowBitmap(0.4);
	}

	if (hasitemsID != nullptr && hasitemsID[0] !=0) {
		items_img[hasitemsID[0] - 1].SetTopLeft(570, 340);
		items_img[hasitemsID[0] - 1].ShowBitmap(0.4); 
	}

	if (hasitemsID != nullptr && hasitemsID[1] != 0) {
		items_img[hasitemsID[1] - 1].SetTopLeft(570, 405);
		items_img[hasitemsID[1] - 1].ShowBitmap(0.4);
	}
}

void game_framework::UI::ShowBullets()
{	
	bullet_img[0].SetTopLeft(10, 372);
	bullet_img[0].ShowBitmap(1.2);
	bullet_img[1].SetTopLeft(10, 406);
	bullet_img[1].ShowBitmap(1.2);
	bullet_img[2].SetTopLeft(10, 440);
	bullet_img[2].ShowBitmap(1.2);

	CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC
	CFont f, *fp;
	char buf[32];
	f.CreatePointFont(200, "Times New Roman");	// 產生 font f; 160表示16 point的字
	fp = pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255, 255, 255));
	sprintf(buf, "%d", Ammo);
	pDC->TextOut(50, 367, buf);
	pDC->TextOut(50, 401, "0");
	pDC->TextOut(50, 435, "0");
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

void game_framework::UI::TakePlayerInfo(int hp, int ammo, int enemy_num, int* hasitemsID, int holdingItem)
{
	HP = hp;
	Ammo = ammo;
	Enemy_Num = enemy_num;
	this->hasitemsID = hasitemsID;
	this->holdingitem = holdingItem;
	SetHealthStatus();
}

void game_framework::UI::SetHealthStatus()
{
	HealthStatus = int((double)HP / 100 * 10);
}

