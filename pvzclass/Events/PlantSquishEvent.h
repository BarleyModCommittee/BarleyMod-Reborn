#pragma once
#include "DLLEvent.h"

/// @brief 植物被碾压事件。
/// @attention 已被碾压的植物依然可以触发此事件，务必注意提防。
/// @param 触发事件的植物。
/// @return 更新后被碾压的植物。返回空指针时该事件被取消。
class PlantSquishEvent : public DLLEvent
{
public:
	PlantSquishEvent() : PlantSquishEvent("onPlantSquish") {};
	PlantSquishEvent(const char* str) : PlantSquishEvent(PVZ::Memory::GetProcAddress(str)) {};
	PlantSquishEvent(int address)
	{
		hookAddress = 0x462B80;
		rawlen = 6;
		BYTE code[] =
		{
			PUSH_PTR_ESP_ADD_V(0x24),
			INVOKE(address),
			ADD_ESP(4),
			TEST_EUX_EVX(REG_EAX, REG_EAX),
			JNZ(4),
			POPAD,
			RETN(4),
			MOV_PTR_ESP_ADD_V_EUX(REG_EAX, 0x24)
		};
		start(STRING(code));
	}
};