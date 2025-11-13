#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 子弹位移结算事件
	/// @param 触发事件的子弹
	/// @return 是否进行位移
	class ProjUpdateMotionEvent : public BoolDLLEventTemplate<0x46DCAD, 5, 0x46DCC0, REG_ESI>
	{
	public:
		ProjUpdateMotionEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		ProjUpdateMotionEvent(const char* name) : BoolDLLEventTemplate() { Init(name); };
		ProjUpdateMotionEvent() : ProjUpdateMotionEvent("onProjectileUpdateMotion") {};
	};
}
