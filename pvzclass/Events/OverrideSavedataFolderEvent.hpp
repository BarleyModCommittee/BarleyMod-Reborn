#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 重载默认存读档目录事件
	/// @param 触发事件时指定的存读档目录（std::string* 形式）
	/// @return 重载的存读档目录的地址（std::string* 形式），非正数会被忽略。
	class OverrideSavedataFolderEvent : public DLLEventTemplate<0x5AF5C0, 7, REG_ECX>
	{
	public:
		OverrideSavedataFolderEvent(const char* str) : DLLEventTemplate() { Init(str); };
		OverrideSavedataFolderEvent(int address) : DLLEventTemplate() { Init(address); };
		OverrideSavedataFolderEvent() : OverrideSavedataFolderEvent("OverrideSavedataFolder") {};
		virtual void InitExtra(AsmBuilder& builder)
		{
			builder.test_reg_reg(REG_EAX, REG_EAX).jle_rel(4).mov_mem_esp_add_imm8_reg(0x18, REG_EAX);
		}
	};
}
