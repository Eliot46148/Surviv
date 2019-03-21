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
		bool isGetting();
	private:
		bool is_Gettting = false;
	};
}