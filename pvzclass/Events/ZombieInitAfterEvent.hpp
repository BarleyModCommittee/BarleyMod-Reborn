#pragma once
#include "DLLEvent.h"

/// @brief 僵尸初始化完成事件
/// @param 初始化的 Zombie 的基址。
class ZombieInitAfterEvent : public DLLEventTemplate<0x524035, 5, REG_EDI>
{
public:
	ZombieInitAfterEvent(const char* str) : DLLEventTemplate() { Init(str); };
	ZombieInitAfterEvent(int address) : DLLEventTemplate() { Init(address); };
	ZombieInitAfterEvent() : DLLEventTemplate() { Init("onZombieInitAfter"); };
};