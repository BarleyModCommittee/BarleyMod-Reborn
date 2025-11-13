#pragma once
#include "DLLEvent.h"

/// @brief 植物因生命值小于 0 被移除事件。
/// @param 触发事件的植物。
/// @return 该植物是否被移除。
class PlantDieLowHealthEvent : public DLLEventTemplate<0x463EDD, 6, REG_EBX>
{
public:
	PlantDieLowHealthEvent(const char* str) : DLLEventTemplate() { Init(str); };
	PlantDieLowHealthEvent(int address) : DLLEventTemplate() { Init(address); };
	PlantDieLowHealthEvent() : DLLEventTemplate() { Init("onPlantDieLowHealth"); };
	void InitExtra(AsmBuilder& builder)
	{
		BYTE code[] =
		{
			TEST_AL_AL,
			JE(14),

			PUSH_EBX,
			INVOKE(0x4679B0),

			POPAD,
			MOV_ECX(0x463EE3),
			JMP_REG32(REG_ECX)
		};

		builder.add_bytes(STRING(code));
	}
};