#pragma once
#include "DLLEvent.h"

/// @brief 物品被点击事件。
/// @note 已收集的物品可以再次触发此事件，注意过滤。
/// @param 依次为：触发事件的物品、点击次数。
/// @return 是否继续结算原版过程。
class CoinMouseDownEvent : public BoolDLLEventTemplate<0x432C47, 5, 0x432DBA, MEM_ESP_ADD(0x7C), REG_ESI>
{
public:
	CoinMouseDownEvent() : CoinMouseDownEvent("onCoinMouseDown") {};
	CoinMouseDownEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
	CoinMouseDownEvent(int address) : BoolDLLEventTemplate() { Init(address); };
};