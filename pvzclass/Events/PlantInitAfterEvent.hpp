#pragma once
#include "DLLEvent.h"

/// @brief 植物初始化完成事件
/// @param 触发事件的植物
class PlantInitAfterEvent : public DLLEventTemplate<0x45E7AF, 7, MEM_ESP_ADD(0x28)>
{
public:
	PlantInitAfterEvent(const char* str) : DLLEventTemplate() { Init(str); };
	PlantInitAfterEvent(int address) : DLLEventTemplate() { Init(address); };
	PlantInitAfterEvent() : PlantInitAfterEvent("onPlantInitAfter") {};
};