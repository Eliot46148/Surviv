#pragma once
#include "BasicObject.h"

/* �����{ */
namespace game_framework {
	class Blood : public BasicObject {
	public:
		Blood();
		Blood(int x, int y);
		void OnMove();					// Timer�p��
		void OnShow();					// ���
		void LoadBitMap();		
		bool IsDead();					// �^��Is_Dead
	private:
		int timer;						// �p�ɾ�
		bool is_Dead;					// �O�_�w�W�L�s�b�ɶ�
		const int survival_time = 15;	// �s�b�ɶ���15�V
	};
}