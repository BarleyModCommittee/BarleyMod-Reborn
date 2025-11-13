#pragma once
#include "DLLEvent.h"

/// @brief 卡槽卡牌被点选事件。
/// @note 时机上先于原版的指令。
/// @param 触发事件的卡槽卡牌。
/// @return 是否继续结算原版的指令。
class SeedPacketMouseDownEvent : public BoolDLLEventTemplate<0x4885C0, 6, 0x488EA6, REG_EBP>
{
public:
	SeedPacketMouseDownEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
	SeedPacketMouseDownEvent(int address) : BoolDLLEventTemplate() { Init(address); };
	SeedPacketMouseDownEvent() : SeedPacketMouseDownEvent("onSeedPacketMouseDown") {};
};

class SeedCardClickEvent : public SeedPacketMouseDownEvent
{
public:
	SeedCardClickEvent(const char* str) : SeedPacketMouseDownEvent(str) {};
	SeedCardClickEvent(int address) : SeedPacketMouseDownEvent(address) {};
	SeedCardClickEvent() : SeedPacketMouseDownEvent("onSeedCardClick") {};
};