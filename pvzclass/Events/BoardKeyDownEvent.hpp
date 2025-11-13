#pragma once
#include "DLLEvent.h"

/// @brief 关卡内键盘按键事件。
/// @note 优先级高于原版事件。
/// @param 依次为：触发事件的 Board，按键的 KeyCode。
/// @return 是否继续结算原版事件。
class BoardKeyDownEvent : public BoolDLLEventTemplate<0x41B820, 6, 0x41B946, MEM_ESP_ADD(0x24), REG_ECX>
{
public:
	BoardKeyDownEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
	BoardKeyDownEvent(int address) : BoolDLLEventTemplate() { Init(address); };
	BoardKeyDownEvent() : BoolDLLEventTemplate() { Init("onBoardKeyDown"); };
};