#pragma once
#include "DLLEvent.h"

/// @brief 僵尸被魅惑事件
/// @param 触发事件的僵尸
/// @return 是否保留该事件。若为“否”，此次魅惑将被取消。
class ZombieHypnotizeEvent : public DLLEvent
{
public:
	ZombieHypnotizeEvent() : ZombieHypnotizeEvent("onZombieHypnotize") {};
	ZombieHypnotizeEvent(const char* str) : ZombieHypnotizeEvent(PVZ::Memory::GetProcAddress(str)) {};
	ZombieHypnotizeEvent(int address)
	{
		hookAddress = 0x52FA60;
		rawlen = 10;
		BYTE code[] = { PUSH_ESI, INVOKE(address), ADD_ESP(4), TEST_AL_AL, JNZ(2), POPAD, RET };
		start(STRING(code));
	}
};