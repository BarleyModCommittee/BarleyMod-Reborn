#pragma once
#include "DLLEvent.h"

/// @brief 一次性植物发动效果事件
/// @param 触发事件的植物
class PlantDoSpecialEvent : public DLLEventTemplate<0x4666A0, 6, MEM_ESP_ADD(0x24)>
{
public:
	PlantDoSpecialEvent(const char* str) : DLLEventTemplate() { Init(str); };
	PlantDoSpecialEvent(int address) : DLLEventTemplate() { Init(address); };
	PlantDoSpecialEvent() : DLLEventTemplate() { Init("onPlantDoSpecial"); };
};