#pragma once
#include "DLLEvent.h"

/// @brief 卡槽卡牌更新事件。
/// @note 时机上先于原版的更新。
/// @param 触发事件的卡槽卡牌。
/// @return 是否继续结算原版的过程。
class SeedPacketUpdateEvent : public DLLEventTemplate<0x487272, 7, 0x487375, REG_EDI>
{
public:
	SeedPacketUpdateEvent(const char* str) : DLLEventTemplate() { Init(str); };
	SeedPacketUpdateEvent(int address) : DLLEventTemplate() { Init(address); };
	SeedPacketUpdateEvent() : DLLEventTemplate() { Init("onSeedPacketUpdate"); };
};