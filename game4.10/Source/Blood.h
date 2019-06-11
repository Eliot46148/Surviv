#pragma once
#include "BasicObject.h"

/* 控制血漬 */
namespace game_framework {
	class Blood : public BasicObject {
	public:
		Blood();
		Blood(int x, int y);
		void OnMove();					// Timer計時
		void OnShow();					// 顯示
		void LoadBitMap();		
		bool IsDead();					// 回傳Is_Dead
	private:
		int timer;						// 計時器
		bool is_Dead;					// 是否已超過存在時間
		const int survival_time = 15;	// 存在時間為15幀
	};
}