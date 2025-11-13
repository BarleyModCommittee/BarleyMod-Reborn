#pragma once
#include "DLLEvent.h"

/// @brief 获取基础阳光消耗事件
/// @note 时机上先于所有判定
/// @param 卡牌类型
class CalcSunCostEvent : public IntDLLEventTemplate<0x467B06, 6, 0, 0, 0, REG_EAX, true, REG_EAX>
{
public:
	CalcSunCostEvent() : IntDLLEventTemplate() { Init("getCardCost"); };
	CalcSunCostEvent(const char* str) : IntDLLEventTemplate() { Init(str); };
	CalcSunCostEvent(int address) : IntDLLEventTemplate() { Init(address); };
};
