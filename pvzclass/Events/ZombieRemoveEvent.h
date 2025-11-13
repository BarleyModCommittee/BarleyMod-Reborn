#pragma once
#include "DLLEvent.h"

/// @brief 僵尸被移除事件
/// @param 触发事件的僵尸
/// @note 僵尸被移除的原因多种多样，即使是关卡僵尸预览界面的僵尸被移除也会触发该事件
class ZombieRemoveEvent : public DLLEventTemplate<0x530510, 6, REG_ECX>
{
public:
	ZombieRemoveEvent() : DLLEventTemplate() { Init("onZombieRemove"); };
	ZombieRemoveEvent(const char* str) : DLLEventTemplate() { Init(str); };
	ZombieRemoveEvent(int address) : DLLEventTemplate() { Init(address); };
};