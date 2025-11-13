#pragma once
#include "DLLEvent.h"

/// @brief 豌豆穿过火炬树桩的着火事件
/// @param 即将变为火球的豌豆
class PeaOnFireEvent : public DLLEventTemplate<0x46EBC0, 5, REG_ECX>
{
public:
	PeaOnFireEvent(const char* str) : DLLEventTemplate() { Init(str); };
	PeaOnFireEvent(int address) : DLLEventTemplate() { Init(address); };
	PeaOnFireEvent() : PeaOnFireEvent("onPeaOnFire") {};
};