#pragma once
#include "DLLEvent.h"

/// @brief IZ 关卡初始化事件
/// @note 此时脑子生成已完成，但植物尚未放置。
/// @param 触发事件的 Challenge
/// @return 是否生成关卡默认生成的植物
class IZInitAfterBrainEvent : public BoolDLLEventTemplate<0x42A981, 6, 0x42B277, REG_EDI>
{
public:
	IZInitAfterBrainEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
	IZInitAfterBrainEvent(int address) : BoolDLLEventTemplate() { Init(address); };
	IZInitAfterBrainEvent() : BoolDLLEventTemplate() { Init("onIZInitAfterBrain"); };
};
