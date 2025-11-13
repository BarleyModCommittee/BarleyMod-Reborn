#pragma once
#include "DLLEvent.h"

/// @brief 子弹创建事件
/// @note 杨桃和投手僵尸的子弹不触发这个事件。
/// @param 被创建的子弹
class ProjectileCreateEvent : public DLLEventTemplate<0x40D652, 5, REG_EAX>
{
public:
	ProjectileCreateEvent(const char* str) : DLLEventTemplate() { Init(str); };
	ProjectileCreateEvent(int address) : DLLEventTemplate() { Init(address); };
	ProjectileCreateEvent() : ProjectileCreateEvent("onProjectileCreate") {};
};