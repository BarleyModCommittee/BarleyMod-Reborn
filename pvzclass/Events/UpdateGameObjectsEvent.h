#pragma once
#include "DLLEvent.h"

/// @brief 更新 GameObject 事件。\n
///		时序上先于 PVZ 本体的更新函数。
/// @param 更新的 Board。
class UpdateGameObjectsEvent : public DLLEventTemplate<0x4130D0, 5, REG_EBX>
{
public:
	UpdateGameObjectsEvent(const char* str) : DLLEventTemplate() { Init(str); };
	UpdateGameObjectsEvent(int address) : DLLEventTemplate() { Init(address); };
	UpdateGameObjectsEvent() : DLLEventTemplate() { Init("onGameObjectsUpdate"); };
};