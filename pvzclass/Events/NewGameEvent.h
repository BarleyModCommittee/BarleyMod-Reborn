#pragma once
#include "DLLEvent.h"

/// @brief 新游戏开始时，PVZGameState变为Preparing之后
/// @note 此时游戏已经完成了关卡的各种加载和准备
class NewGameEvent : public DLLEventTemplate<0x44F8D8, 5>
{
public:
	NewGameEvent(const char* str) : DLLEventTemplate() { Init(str); };
	NewGameEvent(int address) : DLLEventTemplate() { Init(address); };
	NewGameEvent() : DLLEventTemplate() { Init("onNewGame"); };
};