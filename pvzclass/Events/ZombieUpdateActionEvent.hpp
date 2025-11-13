#pragma once
#include "DLLEvent.h"

/// @brief Zombie 行为动作的更新。
/// @note 时机上先于原版的更新。
/// @param 更新的 Zombie
class ZombieUpdateActionEvent : public DLLEventTemplate<0x52B112, 6, REG_EAX>
{
public:
	ZombieUpdateActionEvent() : DLLEventTemplate() { Init("onZombieUpdateAction"); };
	ZombieUpdateActionEvent(const char* str) : DLLEventTemplate() { Init(str); };
	ZombieUpdateActionEvent(int address) : DLLEventTemplate() { Init(address); };
};
