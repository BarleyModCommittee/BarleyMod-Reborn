#pragma once
#include "DLLEvent.h"

/// @brief IZ 关卡通关事件
/// @param 触发事件的 Challenge
class IZLevelCompleteEvent : public DLLEventTemplate<0x42B8FC, 7, REG_ECX>
{
public:
	IZLevelCompleteEvent(const char* str) : DLLEventTemplate() { Init(str); };
	IZLevelCompleteEvent(int address) : DLLEventTemplate() { Init(address); };
	IZLevelCompleteEvent() : DLLEventTemplate() { Init("onIZLevelComplete"); };
};