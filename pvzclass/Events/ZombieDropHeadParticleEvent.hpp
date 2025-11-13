#pragma once
#include "DLLEvent.h"

/// @brief 僵尸掉头的粒子效果处理事件。
/// @param 触发事件的僵尸、触发事件的粒子效果。
class ZombieDropHeadParticleEvent : public DLLEventTemplate<0x529D0E, 6, REG_EDI, REG_EBX>
{
public:
	ZombieDropHeadParticleEvent() : DLLEventTemplate() { Init("onZombieDropHeadParticle"); };
	ZombieDropHeadParticleEvent(const char* str) : DLLEventTemplate() { Init(str); };
	ZombieDropHeadParticleEvent(int address) : DLLEventTemplate() { Init(address); };
};