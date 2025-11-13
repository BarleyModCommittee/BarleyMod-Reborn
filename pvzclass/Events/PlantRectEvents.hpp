#pragma once
#include "DLLEvent.h"

/// @brief 获取植物受击范围事件
/// @param 依次为：触发事件的植物；受击范围矩形的指针。
/// @retval true 是否使用自定义返回值，跳过原版函数
/// @retval false 执行原版函数
class GetPlantRectEvent : public TrueDLLEventTemplate<0x467EF0, 7, 0x467F85, REG_EAX, REG_ECX>
{
public:
	GetPlantRectEvent() : TrueDLLEventTemplate() { Init("getPlantRect"); };
	GetPlantRectEvent(int proc_addr) : TrueDLLEventTemplate() { Init(proc_addr); }
};

/// @brief 获取植物攻击范围事件
/// @param 依次为：触发事件的植物；植物是否使用副武器，范围矩形的指针。
/// @retval true 是否使用自定义返回值，跳过原版函数
/// @retval false 执行原版函数
class GetPlantAttackRectEvent : public TrueDLLEventTemplate<0x467F90, 5, 0x4681D7, REG_EAX, MEM_ESP_ADD(0x28), REG_ECX>
{
public:
	GetPlantAttackRectEvent() : TrueDLLEventTemplate() { Init("getPlantAttackRect"); };
	GetPlantAttackRectEvent(int proc_addr) : TrueDLLEventTemplate() { Init(proc_addr); }
};
