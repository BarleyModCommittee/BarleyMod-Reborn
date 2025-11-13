#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief Board 更新描述事件
	/// @param 触发事件的 Board
	/// @return 是否使用原版的描述文本
	class BoardCustomTooltipEvent : public BoolDLLEventTemplate<0x40F25D, 5, 0x40EFBD, REG_ESI>
	{
	public:
		BoardCustomTooltipEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		BoardCustomTooltipEvent(const char* name) : BoolDLLEventTemplate() { Init(name); };
		BoardCustomTooltipEvent() : BoardCustomTooltipEvent("onBoardCustomTooltip") {};
	};
}
