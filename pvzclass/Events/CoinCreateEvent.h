#pragma once
#include "DLLEvent.h"

/// @brief Coin创建事件
/// @param 触发事件的Coin
class CoinCreateEvent : public DLLEventTemplate<0x40CCCE, 8, REG_EAX>
{
public:
	CoinCreateEvent() : CoinCreateEvent("onCoinCreate") {};
	CoinCreateEvent(const char* str) : DLLEventTemplate() { Init(str); };
	CoinCreateEvent(int address) : DLLEventTemplate() { Init(address); };
};
