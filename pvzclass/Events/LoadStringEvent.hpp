#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 读取资源字符串文件事件
	class LoadStringEvent : public DLLEventTemplate<0x452976, 6>
	{
	public:
		LoadStringEvent(int address) : DLLEventTemplate() { Init(address); };
		LoadStringEvent(const char* name) : DLLEventTemplate() { Init(name); };
		LoadStringEvent() : LoadStringEvent("onLoadString") {};
	};
}
