#pragma once
#include "DLLEvent.h"

/// @brief IZ 关卡初始化完成事件
/// @param 触发事件的 Challenge 所在的 Board
class IZLevelStartAfterEvent : public DLLEventTemplate<0x42B286, 7, REG_EDX>
{
public:
	IZLevelStartAfterEvent(const char* str) : DLLEventTemplate() { Init(str); };
	IZLevelStartAfterEvent(int address) : DLLEventTemplate() { Init(address); };
	IZLevelStartAfterEvent() : DLLEventTemplate() { Init("onIZLevelStartAfter"); };
};