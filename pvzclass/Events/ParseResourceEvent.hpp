#pragma once
#include "DLLEvent.h"

/// @brief 解析资源配置文件事件。
/// @note 时机发生在 resources.xml 解析成功后。
/// @note 虽然参数列表非空，但实际上目标函数不需要参数。
class ParseResourceEvent : public DLLEventTemplate<0x451A0D, 7, REG_EAX>
{
public:
	ParseResourceEvent() : ParseResourceEvent("onParseResource") {};
	ParseResourceEvent(const char* str) : DLLEventTemplate() { Init(str); };
	ParseResourceEvent(int address) : DLLEventTemplate() { Init(address); };
};