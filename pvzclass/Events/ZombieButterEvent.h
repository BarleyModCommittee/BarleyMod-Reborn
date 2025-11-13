#pragma once
#include "DLLEvent.h"

/// @brief 僵尸被黄油命中事件
/// @param 触发事件的僵尸
/// @note 无论是否免疫黄油，该事件都会被触发。
class ZombieButterEvent : public DLLEventTemplate<0x5326D0, 10, REG_EAX>
{
public:
	ZombieButterEvent() : DLLEventTemplate() { Init("onZombieButter"); };
	ZombieButterEvent(const char* str) : DLLEventTemplate() { Init(str); };
	ZombieButterEvent(int address) : DLLEventTemplate() { Init(address); };
};