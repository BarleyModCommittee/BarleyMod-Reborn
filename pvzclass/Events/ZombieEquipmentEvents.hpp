#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 僵尸失去盾牌事件
	/// @param 触发事件时的僵尸
	/// @bug 与已存在的事件重复。
	class ZombieDetachShieldEvent : public DLLEventTemplate<0x5330E0, 5, REG_EAX>
	{
	public:
		ZombieDetachShieldEvent(int address) : DLLEventTemplate() { Init(address); };
		ZombieDetachShieldEvent(const char* name) : DLLEventTemplate() { Init(name); };
		ZombieDetachShieldEvent() : ZombieDetachShieldEvent("onZombieDetachShield") {};
	};

	/// @brief 僵尸掉头盔事件
	/// @param 触发事件的僵尸
	class ZombieDropHelmEvent : public DLLEventTemplate<0x530E46, 6, REG_EBX>
	{
	public:
		ZombieDropHelmEvent(int address) : DLLEventTemplate() { Init(address); };
		ZombieDropHelmEvent(const char* name) : DLLEventTemplate() { Init(name); };
		ZombieDropHelmEvent() : ZombieDropHelmEvent("onZombieDropHelm") {};
	};
}