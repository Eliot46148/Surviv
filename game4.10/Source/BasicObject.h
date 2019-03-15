#pragma once

namespace game_framework {
	class BasicObject {
	public:
		void OnMove();
		void OnShow();
		void SetXY();
		bool isAlive();
		bool isThourghable();
		bool isBreakable();
		virtual void LoadBitMap() = 0;
	protected:
		int speed;
		int HP;
		int size;
	};
}