#pragma once

namespace game_framework {
class BasicObject
{
    public:
        BasicObject();								//��l��
        void OnMove();								//���󪺲���

        void OnShow();
        void setMovingMode(int, bool);
		void SetCamera(int, int);

        virtual void SetXY(int nx, int ny);			//�]�wXY�y��

        virtual void LoadBitMap() = 0;				//���JBMP����
        virtual void SetAlive(bool flag);			//�]�w�O�_�s��

        virtual bool isAlive();						//�O�_�s��
        virtual bool isBreakable();					//�i�_�}�a

        virtual int GetX();							//���oX�y��
        virtual int GetY();							//���oY�y��
        virtual int GetHeight();					//���o����
        virtual int GetWidth();						//���o�e��


    protected:
        CMovingBitmap bmp;							//BMP����
        int speed;									//�t��
        int HP;										//�ͩR
        int Height, Width;							//�e�P��
        int x, y, dx, dy;							//x,y�y��
		int camera_x, camera_y;						//camera��x�My�y��
        float showMagnification;					//��ܤ��
        bool can_breakable;							//�i�H�}�a
        bool is_alive;								//�s��
        bool can_move;								//�i����
        bool isMovingDown;							//�V�U����
        bool isMovingLeft;							//�V������
        bool isMovingRight;							//�V�k����
        bool isMovingUp;							//�V�W����

};
}