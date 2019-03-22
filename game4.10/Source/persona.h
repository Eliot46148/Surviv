#pragma once
#include "BasicObject.h"

namespace game_framework {
	class persona : public BasicObject
	{
	public:
		persona();
		void CatchItem();
		virtual void LoadBitMap();
		virtual void OnShow();
		void SetGetting(bool flag);
		void setCan_move(bool flag);
		bool isGetting();
		bool isCan_Right();
		bool isCan_Left();
		bool isCan_Down();
		bool isCan_UP();

	private:
		bool is_Gettting = false;
	};
}