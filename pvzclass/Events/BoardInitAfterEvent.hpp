#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief Board 初始化完毕事件。
	/// @param 初始化的 Board 对象
	class BoardInitAfterEvent : public DLLEventTemplate<0x408668, 6, REG_EAX>
	{
	public:
		BoardInitAfterEvent(const char* str) : DLLEventTemplate() { Init(str); };
		BoardInitAfterEvent(int address) : DLLEventTemplate() { Init(address); };
		BoardInitAfterEvent() : DLLEventTemplate() { Init("onBoardInitAfter"); };
	};
}