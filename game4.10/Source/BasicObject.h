#pragma once

namespace game_framework {
class BasicObject
{
    public:
        BasicObject();								//初始化
        void OnMove();								//物件的移動

        void OnShow();
        void setMovingMode(int, bool);
		void SetCamera(int, int);

        virtual void SetXY(int nx, int ny);			//設定XY座標

        virtual void LoadBitMap() = 0;				//載入BMP圖檔
        virtual void SetAlive(bool flag);			//設定是否存活

        virtual bool isAlive();						//是否存活
        virtual bool isBreakable();					//可否破壞

        virtual int GetX();							//取得X座標
        virtual int GetY();							//取得Y座標
        virtual int GetHeight();					//取得高度
        virtual int GetWidth();						//取得寬度


    protected:
        CMovingBitmap bmp;							//BMP圖檔
        int speed;									//速度
        int HP;										//生命
        int Height, Width;							//寬與高
        int x, y, dx, dy;							//x,y座標
		int camera_x, camera_y;						//camera的x和y座標
        float showMagnification;					//顯示比例
        bool can_breakable;							//可以破壞
        bool is_alive;								//存活
        bool can_move;								//可移動
        bool isMovingDown;							//向下移動
        bool isMovingLeft;							//向左移動
        bool isMovingRight;							//向右移動
        bool isMovingUp;							//向上移動

};
}