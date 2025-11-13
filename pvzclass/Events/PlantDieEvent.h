#pragma once
#include "DLLEvent.h"

/// @brief 植物消失事件
/// @param 触发事件的植物
/// @note 植物消失原因多种多样：被铲掉、被啃食、一次性植物生效、紫卡植物升级等都会触发
class PlantDieEvent : public DLLEventTemplate<0x4679B9, 7, REG_EBP>
{
public:
	PlantDieEvent(const char* str) : DLLEventTemplate() { Init(str); };
	PlantDieEvent(int address) : DLLEventTemplate() { Init(address); };
	PlantDieEvent() : DLLEventTemplate() { Init("onPlantDie"); };
};