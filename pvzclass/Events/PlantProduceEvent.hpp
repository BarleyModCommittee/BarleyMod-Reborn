#pragma once
#include "DLLEvent.h"

/// @brief 植物产出物品事件。
/// @param 触发事件的植物
/// @return 是否继续产出原版物品。
class PlantProduceEvent : public BoolDLLEventTemplate<0x45FAA7, 6, 0x45FB64, REG_EDI>
{
public:
	PlantProduceEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
	PlantProduceEvent(int address) : BoolDLLEventTemplate() { Init(address); };
	PlantProduceEvent() : PlantProduceEvent("onPlantProduce") {};
};