#pragma once
#include "DLLEvent.h"

/// @brief 小推车启动事件
/// @param 触发事件的小推车
class LawnmowerStartEvent : public DLLEventTemplate<0x458DB0, 6, REG_ESI>
{
public:
	LawnmowerStartEvent(const char* str) : DLLEventTemplate() { Init(str); };
	LawnmowerStartEvent(int address) : DLLEventTemplate() { Init(address); };
	LawnmowerStartEvent() : DLLEventTemplate() { Init("onLawnmowerStart"); };
};