#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"
#include "Map.h"
#include "Box.h"
#include "persona.h"
#include "items.h"
#include "Bullet.h"
#include "shotBullet.h"
#include <math.h>
#include "Texture.h"
#include "Enemy.h"
#include "Camera.h"
#include "UI.h"
#include "Blood.h"

namespace game_framework {

enum AUDIO_ID  				// �w�q�U�ح��Ī��s��
{
    AUDIO_TITLE,
	AUDIO_STEP,
	AUDIO_PISTOL,
	AUDIO_MACHINEGUN,
	AUDIO_SHOTGUN,
	AUDIO_BANDAGE,
	AUDIO_BATTLE
};
static bool isWin = false;

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C���}�Y�e������
// �C��Member function��Implementation���n����
/////////////////////////////////////////////////////////////////////////////

class CGameStateInit : public CGameState
{
    public:
        CGameStateInit(CGame* g);
        void OnInit();  								// �C������Ȥιϧγ]�w
        void OnBeginState();							// �]�w�C�������һݪ��ܼ�
        void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
        void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
    protected:
        void OnShow();									// ��ܳo�Ӫ��A���C���e��
		void OnMove();
    private:
        CMovingBitmap logo;								// csie��logo
		int delay = 0;
		bool showTip = true;
		bool isMusicLoaded = false;
};
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
// �C��Member function��Implementation���n����
/////////////////////////////////////////////////////////////////////////////

class CGameStateRun : public CGameState
{
    public:
        CGameStateRun(CGame* g);
        ~CGameStateRun();
        void OnBeginState();							// �]�w�C�������һݪ��ܼ�
        void ChangeMovingMode(int _where, bool type);
		bool Hascover(Box *box);
        void OnInit();  								// �C������Ȥιϧγ]�w
        void OnKeyDown(UINT, UINT, UINT);
        void OnKeyUp(UINT, UINT, UINT);
        void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
        void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
        void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
        void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
        void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void Cheat();									// ���ե� �����ӧQ
    protected:
        void OnMove();									// ���ʹC������
        void OnShow();									// ��ܳo�Ӫ��A���C���e��
    private:
        CMovingBitmap dot;								// ������
        Map map;
		UI ui;
		Camera camera;
        vector<Box> box;
        vector<items> item;
        persona player1;
        vector<Bullet> bullet;
        vector<shotBullet> shotbullets;
        vector<Texture> texture;
        vector<Enemy> enemy;
		vector<Blood> blood;
		bool firstlife;									// �O�_���Ĥ@���i�J��state
};

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
// �C��Member function��Implementation���n����
/////////////////////////////////////////////////////////////////////////////

class CGameStateOver : public CGameState
{
    public:
        CGameStateOver(CGame* g);
        void OnBeginState();							// �]�w�C�������һݪ��ܼ�
        void OnInit();
    protected:
        void OnMove();									// ���ʹC������
        void OnShow();									// ��ܳo�Ӫ��A���C���e��
		void OnLButtonDown(UINT nFlags, CPoint point);
    private:
        int counter;	// �˼Ƥ��p�ƾ�
		CMovingBitmap logo[2];
		int delay = 0;
		bool showTip = true;
		bool is_delayed = false;
};

}
