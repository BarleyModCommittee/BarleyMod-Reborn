#pragma once
#include "DLLEvent.h"

/// @brief 植物射击事件
/// @param 触发事件的植物
class PlantShootEvent : public DLLEventTemplate<0x466E0D, 6, REG_EBP>
{
public:
	PlantShootEvent(const char* str) : DLLEventTemplate() { Init(str); };
	PlantShootEvent(int address) : DLLEventTemplate() { Init(address); };
	PlantShootEvent() : PlantShootEvent("onPlantShoot") {};
};