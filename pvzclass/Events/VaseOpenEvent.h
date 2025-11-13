#pragma once
#include "DLLEvent.h"

/// @brief 罐子被开启事件。
/// @note 时机上优先级高于开罐的其他操作。
/// @param 依次为：触发事件的 Challenge、触发该事件的罐子基址。
/// @return 是否继续结算罐子被砸开的事件。返回“否”会阻止罐子被敲开。
class VaseOpenEvent : public BoolDLLEventTemplate<0x429AC0, 6, 0x429DA1, MEM_ESP_ADD(0x28), MEM_ESP_ADD(0x28)>
{
public:
	VaseOpenEvent() : VaseOpenEvent("onVaseOpen") {};
	VaseOpenEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
	VaseOpenEvent(int address) : BoolDLLEventTemplate() { Init(address); };
};