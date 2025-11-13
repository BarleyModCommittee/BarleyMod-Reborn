#pragma once
#include "DLLEvent.h"

/// @brief 解谜关卡完成事件
/// @param 触发事件时的 Challenge
class PuzzlePhaseCompleteEvent : public DLLEventTemplate<0x429980, 6, REG_ECX>
{
public:
	PuzzlePhaseCompleteEvent(const char* str) : DLLEventTemplate() { Init(str); };
	PuzzlePhaseCompleteEvent(int address) : DLLEventTemplate() { Init(address); };
	PuzzlePhaseCompleteEvent() : DLLEventTemplate() { Init("onPuzzlePhaseComplete"); };
};