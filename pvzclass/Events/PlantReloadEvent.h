#pragma once
#include "DLLEvent.h"

/// @brief 植物重新装填事件
/// @param 触发事件的植物，生效倒计时
/// @return 修改后的倒计时
/// @note 植物每隔一段时间就重新装填，此时如果发现僵尸则射击\n
/// 生效倒计时默认为生效间隔减去一个[0,14]的随机数
class PlantReloadEvent : public DLLEvent
{
public:
	PlantReloadEvent() : PlantReloadEvent("onPlantReload") {};
	PlantReloadEvent(const char* str) : PlantReloadEvent(PVZ::Memory::GetProcAddress(str)) {};
	PlantReloadEvent(int address)
	{
		hookAddress = 0x45F8C4;
		rawlen = 6;
		BYTE code[] = { PUSH_ECX, PUSH_ESI, INVOKE(address), ADD_ESP(8), MOV_PTR_ESP_ADD_V_EUX(0, 24) };
		start(STRING(code));
	}
};