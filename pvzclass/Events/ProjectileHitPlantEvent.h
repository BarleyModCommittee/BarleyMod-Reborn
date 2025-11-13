#pragma once
#include "DLLEvent.h"

/// @brief 子弹命中植物事件
/// @param 子弹与被命中的植物
/// @return 被命中的植物地址，0为判定未命中\n
/// 如果返回其它植物也可以做到一些有意思的事情
class ProjectileHitPlantEvent : public DLLEvent
{
public:
	ProjectileHitPlantEvent() : ProjectileHitPlantEvent("onProjectileHitPlant") {};
	ProjectileHitPlantEvent(const char* name) : ProjectileHitPlantEvent(PVZ::Memory::GetProcAddress(name)) {};
	ProjectileHitPlantEvent(int address)
	{
		PVZ::Memory::WriteMemory<BYTE>(0x46CBBF, 0xEB);
		PVZ::Memory::WriteMemory<BYTE>(0x46CBC0, 0x63);
		PVZ::Memory::WriteMemory<BYTE>(0x46CC18, 0xEB);
		PVZ::Memory::WriteMemory<BYTE>(0x46CC19, 0x0A);
		hookAddress = 0x46CC28;
		rawlen = 6;
		BYTE code[] = { CMP_EAX_DWORD(0), JE(22), PUSH_EAX, PUSH_EBP,
				INVOKE(address), ADD_ESP(8), MOV_PTR_ESP_ADD_V_EUX(0, 28)
			};
		start(STRING(code));
	}
};
