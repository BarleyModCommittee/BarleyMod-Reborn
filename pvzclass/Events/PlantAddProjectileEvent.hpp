#pragma once
#include "DLLEvent.h"

class NormalPlantAddProjectileEvent : public DLLEvent
{
public:
	NormalPlantAddProjectileEvent()
	{
		NormalPlantAddProjectileEvent::NormalPlantAddProjectileEvent("onPlantAddProjectile");
	}
	NormalPlantAddProjectileEvent(const char* str)
	{
		NormalPlantAddProjectileEvent(PVZ::Memory::GetProcAddress(str));
	}
	NormalPlantAddProjectileEvent(int address)
	{
		hookAddress = 0x4672B5;
		rawlen = 6;
		BYTE code[] =
		{
			PUSH_PTR_ESP_ADD_V(0x54),
			PUSH_EAX,
			PUSH_EBP,
			INVOKE(address),
			ADD_ESP(0x0C),

			TEST_AL_AL,
			JNZ(7),
			POPAD,
			PUSHDWORD(0x467319),
			RET
		};
		start(STRING(code));
	}
};

class StarFruitAddProjectileEvent : public DLLEvent
{
public:
	StarFruitAddProjectileEvent()
	{
		StarFruitAddProjectileEvent::StarFruitAddProjectileEvent("onPlantTakeEatDamage");
	}
	StarFruitAddProjectileEvent(const char* str)
	{
		StarFruitAddProjectileEvent(PVZ::Memory::GetProcAddress(str));
	}
	StarFruitAddProjectileEvent(int address)
	{
		hookAddress = 0x45F816;
		rawlen = 7;
		BYTE code[] =
		{
			PUSH(0),
			PUSH_EDI,
			PUSH_ESI,
			INVOKE(address),
			ADD_ESP(0x0C),

			TEST_AL_AL,
			JNZ(7),
			POPAD,
			PUSHDWORD(0x45F874),
			RET
		};
		start(STRING(code));
	}
};

/// @brief 植物发射子弹事件。
/// @param 按参数列表顺序，依次为：触发事件的植物、生成的子弹、子弹目标僵尸的基址。
/// @return 是否进行原版的初始化过程。
class PlantAddProjectileEvent
{
private:
	NormalPlantAddProjectileEvent* normal_event;
	StarFruitAddProjectileEvent* star_event;
public:
	PlantAddProjectileEvent()
	{
		normal_event = new NormalPlantAddProjectileEvent("onPlantAddProjectile");
		star_event = new StarFruitAddProjectileEvent("onPlantAddProjectile");
	}
	PlantAddProjectileEvent(int address)
	{
		normal_event = new NormalPlantAddProjectileEvent(address);
		star_event = new StarFruitAddProjectileEvent(address);
	}
	void end()
	{
		normal_event->end();
		star_event->end();
	}
};