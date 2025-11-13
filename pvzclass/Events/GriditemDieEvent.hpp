#pragma once
#include "DLLEvent.h"

/// @brief 场地物品移除事件。
/// @param 触发事件的场地物品。
/// @return 是否移除此物品。
class GriditemDieEvent : public BoolDLLEventTemplate<0x44D000, 5, 0x44D06A, REG_ESI>
{
public:
	GriditemDieEvent() : GriditemDieEvent("onGriditemDie") {};
	GriditemDieEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
	GriditemDieEvent(int address) : BoolDLLEventTemplate() { Init(address); };
};