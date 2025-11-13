#pragma once
#include "DLLEvent.h"

/// @brief 宝石迷阵转转看中，一次移动不产生匹配时触发的事件。
/// @param 依次为：左上角的行数，左上角的列数
/// @return 是否拒绝此次移动。
class BegTwistFailMoveEvent : public BoolDLLEventTemplate<0x42053C, 7, 0x420602, REG_ESI, MEM_ESP_ADD(0x3C)>
{
public:
	BegTwistFailMoveEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
	BegTwistFailMoveEvent(int address) : BoolDLLEventTemplate() { Init(address); };
	BegTwistFailMoveEvent() : BoolDLLEventTemplate() { Init("onBegTwistFailMove"); };
};