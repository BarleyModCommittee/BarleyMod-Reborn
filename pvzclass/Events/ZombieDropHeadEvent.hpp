#pragma once
#include "DLLEvent.h"

/// @brief 僵尸掉头事件。
/// @param 受掉头伤害的僵尸的基址、伤害标签
/// @return 是否继续结算致命伤害
class ZombieDropHeadEvent : public DLLEvent
{
public:
	ZombieDropHeadEvent() : ZombieDropHeadEvent("onZombieDropHead") {};
	ZombieDropHeadEvent(const char* str) : ZombieDropHeadEvent(PVZ::Memory::GetProcAddress(str)) {};
	ZombieDropHeadEvent(int address)
	{
		hookAddress = 0x529A30;
		rawlen = 6;
		BYTE code[] =
		{
			PUSH_PTR_ESP_ADD_V(0x28),
			PUSH_PTR_ESP_ADD_V(0x28),
			INVOKE(address),
			ADD_ESP(8),

			TEST_AL_AL,
			JNZ(4),
			POPAD,
			RETN(8)
		};
		start(STRING(code));
	}
};
