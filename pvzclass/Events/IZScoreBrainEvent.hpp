#pragma once
#include "DLLEvent.h"

/// @brief IZ 中，获得脑子积分的事件
/// @param 触发事件的 IZBrain
class IZScoreBrainEvent : public DLLEventTemplate<0x42B8B3, 6, REG_EBX>
{
public:
	IZScoreBrainEvent(const char* str) : DLLEventTemplate() { Init(str); };
	IZScoreBrainEvent(int address) : DLLEventTemplate() { Init(address); };
	IZScoreBrainEvent() : DLLEventTemplate() { Init("onIZScoreBrain"); };
};
