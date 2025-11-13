#pragma once
#include "DLLEvent.h"

/// @brief 僵尸被冻结事件
/// @param 触发事件的僵尸
/// @note 无论是否被冻结，该事件都会被触发。
class ZombieFrozeEvent : public DLLEventTemplate<0x5323C0, 6, REG_EAX>
{
public:
	ZombieFrozeEvent() : DLLEventTemplate() { Init("onZombieFroze"); };
	ZombieFrozeEvent(const char* str) : DLLEventTemplate() { Init(str); };
	ZombieFrozeEvent(int address) : DLLEventTemplate() { Init(address); };
};