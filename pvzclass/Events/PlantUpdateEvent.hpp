#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 植物更新事件。
	/// @param 触发事件的植物。
	/// @return 是否考虑进行此次更新。
	class PlantUpdateEvent : public BoolDLLEventTemplate<0x463E43, 6, 0x463EE8, REG_EBX>
	{
	public:
		PlantUpdateEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		PlantUpdateEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		PlantUpdateEvent() : PlantUpdateEvent("onPlantStolen") {};
	};
}