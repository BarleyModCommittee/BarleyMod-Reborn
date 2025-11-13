#pragma once
#include "DLLEvent.h"

/// @brief 植物创建事件
/// @param 触发事件的植物
/// @note 该事件只对部分来源的植物有效。若需要监测全部植物，参见 PlantInitAfterEvent 。
class PlantCreateEvent : public DLLEventTemplate<0x40D190, 8, REG_EAX>
{
public:
	PlantCreateEvent(const char* str) : DLLEventTemplate() { Init(str); };
	PlantCreateEvent(int address) : DLLEventTemplate() { Init(address); };
	PlantCreateEvent() : DLLEventTemplate() { Init("onPlantCreate"); };
};