#pragma once
#include "DLLEvent.h"

/// @brief 砸罐模式生成罐子事件。
/// @note 事件触发时罐子尚未生成。
/// @param 触发事件的 Challenge。
/// @return 是否继续生成原版罐子。
class VaseBreakerPopulateEvent : public BoolDLLEventTemplate<0x4286F0, 6, 0x4294FA, REG_ESI>
{
public:
	VaseBreakerPopulateEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
	VaseBreakerPopulateEvent(int address) : BoolDLLEventTemplate() { Init(address); };
	VaseBreakerPopulateEvent() : BoolDLLEventTemplate() { Init("onVaseBreakerPopulate"); };
};