#pragma once

namespace game_framework {
class BasicObject
{
    public:
		 BasicObject();
        void OnMove();
        virtual void OnShow();
		virtual void SetXY(int nx, int ny);
		virtual void SetMovingUP(bool flag);
		virtual void SetMovingDown(bool flag);
		virtual void SetMovingLeft(bool flag);
		virtual void SetMovingRight(bool flag);
		virtual void SetAlive(bool flag);
		virtual int GetX();
		virtual int GetY();
		virtual int GetHeight();
		virtual int GetWidth();

		virtual bool isAlive();
		virtual bool isThourghable();
		virtual bool isBreakable();

        virtual void LoadBitMap() = 0;
    protected:
        CMovingBitmap bmp;
        int speed;
        int HP;
        int Height, Width;
        int x, y, dx, dy;
        bool can_breakable, can_thourghable, is_alive, can_move;
        bool isMovingDown, isMovingLeft, isMovingRight, isMovingUp;

};
}