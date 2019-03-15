#include "stdafx.h"
#include "BasicObject.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

namespace game_framework {
	void BasicObject::OnMove()
	{

	}
	void BasicObject::OnShow()
	{
	}
	void BasicObject::SetXY()
	{
	}
	bool BasicObject::isAlive()
	{
		return false;
	}
	bool BasicObject::isThourghable()
	{
		return false;
	}
	bool BasicObject::isBreakable()
	{
		return false;
	}

}
