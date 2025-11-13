#pragma once
#include "DLLEvent.h"

/// @brief 提取资源事件。
/// @note 时机发生在 resources.xml 解析成功后。
/// @param 触发事件的 ResourceManager，读取的资源组名称（char* 形式）
/// @return 若为正数，则读取成功；若为 0，则读取失败；若为负数，结算原版过程。
class ExtractResourceEvent : public DLLEventTemplate<0x474700, 5, MEM_ESP_ADD(0x28), MEM_ESP_ADD(0x28)>
{
public:
	ExtractResourceEvent() : ExtractResourceEvent("onParseResource") {};
	ExtractResourceEvent(const char* str) : DLLEventTemplate() { Init(str); };
	ExtractResourceEvent(int address) : DLLEventTemplate() { Init(address); };
	void InitExtra(AsmBuilder& builder)
	{
		BYTE code[] =
		{
			TEST_EUX_EVX(REG_EAX, REG_EAX),
			JS(17),
			JE(9),

			POPAD,
			MOV_EAX(1),
			RETN(8),

			POPAD,
			XOR_EUX_EVX(REG_EAX, REG_EAX),
			RETN(8),
		};
		builder.add_bytes(STRING(code));
	}
};