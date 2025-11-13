#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 重载蹦极僵尸卡种植条件事件
	/// @param 触发事件的行数、列数，本关放置其他僵尸的最左列数
	/// @return 是否可以种植
	class BungeeCanPlantAtEvent : public DiversionEventTemplate<0x4255E6, 5, 0x425683, 0x425669, REG_ECX, REG_EBX, REG_EDI>
	{
	public:
		BungeeCanPlantAtEvent(const char* str) : DiversionEventTemplate() { Init(str); };
		BungeeCanPlantAtEvent(int address) : DiversionEventTemplate() { Init(address); };
		BungeeCanPlantAtEvent() : BungeeCanPlantAtEvent("IsBungeeCanPlantAt") {};
	};
}
