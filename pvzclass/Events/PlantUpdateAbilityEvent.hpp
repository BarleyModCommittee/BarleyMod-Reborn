#pragma once
#include "DLLEvent.h"

/// @brief 植物特性更新事件。
/// @note 时机上先于保龄球特性。
/// @param 触发事件的植物。
/// @return 是否结算大部分原版特性。若为“否”，则只结算射手和一次性植物的特性。
class PlantUpdateAbilityEvent : public DLLEvent
{
public:
	PlantUpdateAbilityEvent() : PlantUpdateAbilityEvent("onPlantUpdateAbility") {};
	PlantUpdateAbilityEvent(const char* str) : PlantUpdateAbilityEvent(PVZ::Memory::GetProcAddress(str)) {};
	PlantUpdateAbilityEvent(int address)
	{
		hookAddress = 0x463254;
		rawlen = 5;
		BYTE code[] =
		{
			PUSH_EDI,
			INVOKE(address),
			ADD_ESP(4),
			TEST_AL_AL,
			JNZ(8),

			POPAD,
			MOV_ECX(0x4633EE),
			JMP_REG32(REG_ECX),

			POPAD,
			INVOKE(0x453840),
			MOV_ECX(0x463259),
			JMP_REG32(REG_ECX),
		};
		start(STRING(code));
	}
};

namespace PVZEvent
{
	/// @brief 判断植物是否应该发动技能的事件
	/// @note 时机上后于压扁判断和消失判断，但先于蹦极是否抱住的判断。
	/// @param 触发事件的植物
	/// @return 是否继续判定是否应该发动技能。若为否，则不发动技能。
	class JudgetPlantUpdateAbilityEvent : public BoolDLLEventTemplate<0x463217, 7, 0x463410, REG_EDI>
	{
	public:
		JudgetPlantUpdateAbilityEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		JudgetPlantUpdateAbilityEvent(const char* name) : BoolDLLEventTemplate() { Init(name); };
		JudgetPlantUpdateAbilityEvent() : JudgetPlantUpdateAbilityEvent("onZombieDropHelm") {};
	};
}