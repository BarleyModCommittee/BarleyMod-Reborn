#pragma once
#include "DLLEvent.h"

/// @brief Coin收集事件
/// @param 触发事件的Coin
class CoinCollectEvent : public DLLEventTemplate<0x432060, 6, REG_ECX>
{
public:
	CoinCollectEvent() : CoinCollectEvent("onCoinCollect") {};
	CoinCollectEvent(const char* str) : DLLEventTemplate() { Init(str); };
	CoinCollectEvent(int address) : DLLEventTemplate() { Init(address); };
};
