#pragma once
#include "DLLEvent.h"

// 僵尸受伤事件
// 参数：触发事件的僵尸，伤害类型，伤害数值
// 返回值：更新后的伤害值
// 多个事件之间伤害会串联修改，例如基础伤害20
// 第一个监听器翻倍至40，第二个事件监听到的伤害数值就是40
// 如不作其它修改，僵尸最后会受到40点伤害
/// @deprecated
class ZombieHitEvent : public DLLEvent
{
public:
	ZombieHitEvent()
	{
		int procAddress = PVZ::Memory::GetProcAddress("onZombieHit");
		hookAddress = 0x5317C0;
		rawlen = 7;
		BYTE code[] = { PUSH_PTR_ESP_ADD_V(36), PUSH_EAX, PUSH_ESI, INVOKE(procAddress), ADD_ESP(12), MOV_PTR_ESP_ADD_V_EUX(0, 36) };
		start(STRING(code));
	}
};

/// @brief 僵尸受伤事件
/// @param 触发事件的僵尸，伤害类型，伤害数值
/// @return 更新后的伤害值
class ZombieTakeDmgEvent : public DLLEvent
{
public:
	ZombieTakeDmgEvent() : ZombieTakeDmgEvent("onZombieTakeDamage") {};
	ZombieTakeDmgEvent(const char* str) : ZombieTakeDmgEvent(PVZ::Memory::GetProcAddress(str)) {};
	ZombieTakeDmgEvent(int address)
	{
		hookAddress = 0x5317C0;
		rawlen = 7;
		BYTE code[] = { PUSH_PTR_ESP_ADD_V(36), PUSH_EAX, PUSH_ESI, INVOKE(address), ADD_ESP(12), MOV_PTR_ESP_ADD_V_EUX(0, 36) };
		start(STRING(code));
	}
};

namespace PVZEvent
{
	/// @brief 僵尸本体受伤后事件
	/// @note 时机上后于本体受伤，先于后续所有判别。
	/// @param 触发事件的僵尸，伤害数值，伤害标签
	class ZombieTakeBodyDamageAfterEvent : public DLLEventTemplate<0x53131F, 5, MEM_ESP_ADD(0x44), MEM_ESP_ADD(0x44), REG_EBP>
	{
	public:
		ZombieTakeBodyDamageAfterEvent(const char* str) : DLLEventTemplate() { Init(str); };
		ZombieTakeBodyDamageAfterEvent(int address) : DLLEventTemplate() { Init(address); };
		ZombieTakeBodyDamageAfterEvent() : ZombieTakeBodyDamageAfterEvent("onZombieTakeBodyDamageAfter") {};
	};

	/// @brief 僵尸受到非灰烬爆炸伤害事件
	/// @param 触发事件的僵尸
	/// @return 是否受到此次伤害
	class PotatoDamageZombieEvent : public DLLEventTemplate<0x41D93A, 5, REG_ESI>
	{
	public:
		PotatoDamageZombieEvent(int address) : DLLEventTemplate() { Init(address); };
		PotatoDamageZombieEvent(const char* name) : DLLEventTemplate() { Init(name); };
		PotatoDamageZombieEvent() : PotatoDamageZombieEvent("onPotatoDamageZombie") {};
		virtual void InitExtra(AsmBuilder& builder)
		{
			builder.test_al_al().jnz_rel(10).popad().add_reg_imm(REG_ESP, 4).push_imm32(0x41D93F).ret();
		}
	};

	/// @brief 僵尸掉头后，持续受到伤害事件
	/// @param 触发事件的僵尸
	/// @return 僵尸是否受到伤害
	class ZombieWitherEvent : public DiversionEventTemplate<0x52B536, 5, 0x52B544, 0x52B551, REG_EDI>
	{
	public:
		ZombieWitherEvent(int address) : DiversionEventTemplate() { Init(address); };
		ZombieWitherEvent(const char* name) : DiversionEventTemplate() { Init(name); };
		ZombieWitherEvent() : ZombieWitherEvent("onZombieWither") {};
	};
}
