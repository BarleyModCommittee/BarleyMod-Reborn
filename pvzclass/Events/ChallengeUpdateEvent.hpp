#pragma once
#include "DLLEvent.h"

/// @brief 游戏模式特性更新事件。
/// @param 触发事件的 Challenge
/// @return 是否按原版模式更新事件。
class ChallengeUpdateEvent : public BoolDLLEventTemplate<0x4246B0, 6, 0x42470B, REG_EAX>
{
public:
	ChallengeUpdateEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
	ChallengeUpdateEvent(int address) : BoolDLLEventTemplate() { Init(address); };
	ChallengeUpdateEvent() : BoolDLLEventTemplate() { Init("onChallengeUpdate"); };
};
