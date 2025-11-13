#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 获取卡牌背景事件
	/// @param 触发事件的卡牌内容类型，卡牌的模仿植物类型
	/// @return 若为负数，则按原版处理；否则返回卡牌背景的列数。
	class SeedPacketBGColumnEvent : public IntDLLEventTemplate<0x4877FB, 6, 0, 0, 0, REG_ECX, false, REG_EDI, REG_EBX>
	{
	public:
		SeedPacketBGColumnEvent(int address) : IntDLLEventTemplate() { Init(address); };
		SeedPacketBGColumnEvent(const char* name) : IntDLLEventTemplate() { Init(name); };
		SeedPacketBGColumnEvent() : SeedPacketBGColumnEvent("GetSeedPacketBGColumn") {};
		virtual void InitExtra(AsmBuilder& builder)
		{
			builder.cmp_reg_imm(REG_EAX, 0).jl_rel(4);
			builder.mov_mem_esp_add_imm8_reg(0x18, REG_EAX);
		}
	};

	/// @brief 获取卡牌描述事件
	/// @param 触发事件的 TooltipWidget，TooltipWidget 所在的 Board，当前选中的 SeedPacket
	class SeedPacketTooltipEvent : public DLLEventTemplate<0x40FA72, 5, MEM_ESP_ADD(0x34), REG_EBP, REG_ECX>
	{
	public:
		SeedPacketTooltipEvent(int address) : DLLEventTemplate() { Init(address); };
		SeedPacketTooltipEvent(const char* name) : DLLEventTemplate() { Init(name); };
		SeedPacketTooltipEvent() : SeedPacketTooltipEvent("GetSeedPacketTooltip") {};
	};
}
