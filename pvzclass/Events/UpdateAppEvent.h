#pragma once
#include "DLLEvent.h"

/// @brief 游戏程序的更新事件
/// @param 触发事件的 PVZApp
/// @note 该事件无论是否在关卡内都会持续触发
class UpdateAppEvent : public DLLEventTemplate<0x453A50, 7, REG_ECX>
{
public:
	UpdateAppEvent(const char* str) : DLLEventTemplate() { Init(str); };
	UpdateAppEvent(int address) : DLLEventTemplate() { Init(address); };
	UpdateAppEvent() : DLLEventTemplate() { Init("onAppUpdate"); };
};