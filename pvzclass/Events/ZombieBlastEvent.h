#pragma once
#include "DLLEvent.h"

/// @brief 僵尸灰烬事件
/// @param 触发事件的僵尸
/// @note 僵尸受到灰烬伤害就会触发
/// @note 该事件不可被取消。若希望取消该事件以实现免疫灰烬，请考虑 ZombieBurntEvent。
/// @note 该事件不与 ZombieBurntEvent 兼容，请不要同时使用。
/// @see ZombieBurntEvent
class ZombieBlastEvent : public DLLEventTemplate<0x532B70, 6, REG_ECX>
{
public:
	ZombieBlastEvent() : DLLEventTemplate() { Init("onZombieBlast"); };
	ZombieBlastEvent(const char* str) : DLLEventTemplate() { Init(str); };
	ZombieBlastEvent(int address) : DLLEventTemplate() { Init(address); };
};

/// @brief 僵尸受到灰烬伤害事件。
/// @param 触发事件的僵尸
/// @return 是否取消该事件。
/// @note 该事件不与 ZombieBlastEvent 兼容，请不要同时使用。
/// @see ZombieBlastEvent
class ZombieBurntEvent : public BoolDLLEventTemplate<0x532B70, 6, 0x532FF0, REG_ECX>
{
public:
	ZombieBurntEvent() : BoolDLLEventTemplate() { Init("onZombieBurnt"); };
	ZombieBurntEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
	ZombieBurntEvent(int address) : BoolDLLEventTemplate() { Init(address); };
};