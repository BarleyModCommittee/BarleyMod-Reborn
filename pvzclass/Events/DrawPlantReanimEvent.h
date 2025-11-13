#pragma once
#include "DLLEvent.h"

/// @brief 绘制植物动画事件
/// @param 绘制的植物和对应的动画
// 事件触发在颜色计算之后和绘制发生之前
class DrawPlantReanimEvent : public DLLEvent
{
public:
	DrawPlantReanimEvent() : DrawPlantReanimEvent("onDrawPlantReanim") {};
	DrawPlantReanimEvent(const char* str) : DrawPlantReanimEvent(PVZ::Memory::GetProcAddress(str)) {};
	DrawPlantReanimEvent(int address)
	{
		PVZ::Memory::WriteMemory<BYTE>(0x4638C4, 0xEB);
		PVZ::Memory::WriteMemory<BYTE>(0x4638C5, 0x15);
		PVZ::Memory::WriteMemory<BYTE>(0x4638C6, NOP);
		PVZ::Memory::WriteMemory<BYTE>(0x4638C7, NOP);
		PVZ::Memory::WriteMemory<BYTE>(0x4638C8, NOP);
		hookAddress = 0x4638DB;
		rawlen = 5;
		BYTE code[] = { PUSH_EBX, PUSH_PTR_ESP_ADD_V(0x2C), INVOKE(address), ADD_ESP(8),
			POPAD, INVOKE(0x473AE0), JMP(6)
		};
		start(STRING(code));
	}
};
