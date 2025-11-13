#pragma once
#include "DLLEvent.h"

/// @brief Board 游戏更新事件
/// @note 该事件的触发频率受“僵尸快跑”加速影响。
/// @praram 触发事件的 Board 的指针
class BoardUpdateGameEvent : public DLLEventTemplate<0x415926, 6, REG_ECX>
{
public:
	BoardUpdateGameEvent(const char* str) : DLLEventTemplate() { Init(str); };
	BoardUpdateGameEvent(int address) : DLLEventTemplate() { Init(address); };
	BoardUpdateGameEvent() : DLLEventTemplate() { Init("onBoardUpdateGame"); };
};