#pragma once
#include "DLLEvent.h"

/// @brief 僵尸掉落物品事件。
/// @note 已尝试掉落过物品的僵尸不会再次掉落物品。
/// @param 掉落物品的僵尸的地址
class ZombieDropLootEvent : public DLLEventTemplate<0x5301C0, 7, REG_EBX>
{
public:
	ZombieDropLootEvent() : DLLEventTemplate() { Init("onZombieDropLoot"); };
	ZombieDropLootEvent(const char* str) : DLLEventTemplate() { Init(str); };
	ZombieDropLootEvent(int address) : DLLEventTemplate() { Init(address); };
};