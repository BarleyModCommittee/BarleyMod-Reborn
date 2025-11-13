#pragma once
#include "DLLEvent.h"

/// @brief 判断僵尸是否可攻击植物事件。
/// @note 时机先于一切原版结算。
/// @param 触发事件的僵尸，触发事件的植物，僵尸攻击类型
/// @return 若为正数，则可以索敌；若为 0，则不可索敌；若为负数，结算原版过程。
class ZombieTargetPlantEvent : public DLLEvent
{
public:
	ZombieTargetPlantEvent() : ZombieTargetPlantEvent("onZombieTargetPlant") {};
	ZombieTargetPlantEvent(const char* str) : ZombieTargetPlantEvent(PVZ::Memory::GetProcAddress(str)) {};
	ZombieTargetPlantEvent(int address)
	{
		hookAddress = 0x52E4C0;
		rawlen = 5;
		BYTE code[] =
		{
			PUSH_PTR_ESP_ADD_V(0x28),
			PUSH_PTR_ESP_ADD_V(0x28),
			PUSH_ECX,
			INVOKE(address),
			ADD_ESP(12),

			TEST_EUX_EVX(REG_EAX, REG_EAX),
			JS(17),
			JE(9),

			POPAD,
			MOV_EAX(1),
			RETN(8),

			POPAD,
			XOR_EUX_EVX(REG_EAX, REG_EAX),
			RETN(8),
		};
		start(STRING(code));
	}
};