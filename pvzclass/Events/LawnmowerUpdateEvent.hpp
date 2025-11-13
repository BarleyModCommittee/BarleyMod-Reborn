#pragma once
#include "DLLEvent.h"

/// @brief 小推车更新事件。
/// @note 时机上先于原版更新所有操作。
/// @param 触发事件的小推车的基址。
/// @return 是否继续结算原版更新。
class LawnmowerUpdateEvent : public BoolDLLEventTemplate<0x4586E0, 5, 0x45870F, MEM_ESP_ADD(0x24)>
{
public:
	LawnmowerUpdateEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
	LawnmowerUpdateEvent(int address) : BoolDLLEventTemplate() { Init(address); };
	LawnmowerUpdateEvent() : BoolDLLEventTemplate() { Init("onLawnmowerUpdate"); };
};