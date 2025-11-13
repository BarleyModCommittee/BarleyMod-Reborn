#pragma once
#include "DLLEvent.h"

/// @brief Griditem 更新事件
/// @param 更新的 Griditem
/// @note 时机上先于原版更新。
class GriditemUpdateEvent : public DLLEventTemplate<0x44E5E0, 5, REG_EAX>
{
public:
	GriditemUpdateEvent() : GriditemUpdateEvent("onGriditemUpdate") {};
	GriditemUpdateEvent(const char* str) : DLLEventTemplate() { Init(str); };
	GriditemUpdateEvent(int address) : DLLEventTemplate() { Init(address); };
};