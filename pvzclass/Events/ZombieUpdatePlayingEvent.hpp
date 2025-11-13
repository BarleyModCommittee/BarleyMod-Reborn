#pragma once
#include "DLLEvent.h"

/// @brief Zombie 角色的更新，被冻结、黄油定身时也会结算。
/// @note 时机上先于原版的更新。
/// @param 更新的 Zombie
class ZombieUpdatePlayingEvent : public DLLEventTemplate<0x52B340, 6, REG_EDI>
{
public:
	ZombieUpdatePlayingEvent() : DLLEventTemplate() { Init("onZombieUpdatePlaying"); };
	ZombieUpdatePlayingEvent(const char* str) : DLLEventTemplate() { Init(str); };
	ZombieUpdatePlayingEvent(int address) : DLLEventTemplate() { Init(address); };
};