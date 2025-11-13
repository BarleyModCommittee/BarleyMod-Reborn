#pragma once
#include "DLLEvent.h"

/// @brief 绘制Dialog返回前，用于追加绘制Edit
/// @param Dialog的地址
class DialogDrawEvent : public DLLEventTemplate<0x457959, 6, REG_ESI, REG_EDI>
{
public:
	DialogDrawEvent() : DLLEventTemplate() { Init("onDialogDraw"); };
	DialogDrawEvent(const char* str) : DLLEventTemplate() { Init(str); };
	DialogDrawEvent(int address) : DLLEventTemplate() { Init(address); };
};