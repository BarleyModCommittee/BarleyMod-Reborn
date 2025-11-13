#pragma once
#include "DLLEvent.h"

/// @brief 植物被偷走事件。
/// @param 触发事件的植物。
class PlantStolenEvent : public DLLEventTemplate<0x5304B6, 7, REG_EAX>
{
public:
	PlantStolenEvent(const char* str) : DLLEventTemplate() { Init(str); };
	PlantStolenEvent(int address) : DLLEventTemplate() { Init(address); };
	PlantStolenEvent() : PlantStolenEvent("onPlantStolen") {};
};