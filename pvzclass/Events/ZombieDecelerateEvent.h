#pragma once
#include "DLLEvent.h"

/// @brief 僵尸被减速事件
/// @param 触发事件的僵尸
/// @note 无论是否免疫减速，该事件都会被触发。
class ZombieDecelerateEvent : public DLLEventTemplate<0x530950, 5, REG_EAX>
{
public:
	ZombieDecelerateEvent() : DLLEventTemplate() { Init("onZombieDecelerate"); };
	ZombieDecelerateEvent(const char* str) : DLLEventTemplate() { Init(str); };
	ZombieDecelerateEvent(int address) : DLLEventTemplate() { Init(address); };
};