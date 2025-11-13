#pragma once
#include "DLLEvent.h"

/// @brief Challenge 初始化的事件。
/// @note 触发时机先于 BoardInitAfterEvent。
/// @param 触发事件的 Challenge
class ChallengeInitAfterEvent : public DLLEventTemplate<0x41F30D, 6, REG_EDI>
{
public:
	ChallengeInitAfterEvent(const char* str) : DLLEventTemplate() { Init(str); };
	ChallengeInitAfterEvent(int address) : DLLEventTemplate() { Init(address); };
	ChallengeInitAfterEvent() : DLLEventTemplate() { Init("onChallengeInitAfter"); };
};

/// @brief 关卡初始化后的事件。
/// @param 触发事件的 Challenge
class ChallengeInitLevelAfterEvent : public DLLEventTemplate<0x41F6D8, 5, REG_EDI>
{
public:
	ChallengeInitLevelAfterEvent(const char* str) : DLLEventTemplate() { Init(str); };
	ChallengeInitLevelAfterEvent(int address) : DLLEventTemplate() { Init(address); };
	ChallengeInitLevelAfterEvent() : DLLEventTemplate() { Init("onChallengeInitLevelAfter"); };
};