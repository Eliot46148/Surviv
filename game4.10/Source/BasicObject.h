#pragma once

namespace game_framework {
	class BasicObject {
	public:
		BasicObject();
		void OnMove();
		virtual void OnShow();
		void SetXY(int nx, int ny);
		void SetMovingUP(bool flag);
		void SetMovingDown(bool flag);
		void SetMovingLeft(bool flag);
		void SetMovingRight(bool flag);
		void SetAlive(bool flag);
		int GetX();
		int GetY();


		bool isAlive();
		bool isThourghable();
		bool isBreakable();

		virtual void LoadBitMap() = 0;
	protected:
		CMovingBitmap bmp;
		int speed;
		int HP;
		int Height,Width;
		int x, y, dx, dy;
		bool can_breakable, can_thourghable, is_alive, can_move;
		bool isMovingDown, isMovingLeft, isMovingRight, isMovingUp;

	};
}