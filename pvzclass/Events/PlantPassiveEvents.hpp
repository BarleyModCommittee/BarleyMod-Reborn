#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 判断植物是否具有保护伞防护效果的事件
	/// @note 该事件会导致原版的判断失效。
	/// @param 触发事件的植物，检查的行数，检查的列数
	/// @return 该植物是否能起到保护伞的防御效果。若为是，则返回值应当为该植物的基址。
	class CheckUmbrellaEvent : public ThreeStateEventTemplate<0x41D3F0, 8, 0x41D446, 0x41D437, MEM_ESP_ADD(0x24)>
	{
	public:
		CheckUmbrellaEvent(const char* str) : ThreeStateEventTemplate() { Init(str); };
		CheckUmbrellaEvent(int address) : ThreeStateEventTemplate() { Init(address); };
		CheckUmbrellaEvent() : CheckUmbrellaEvent("IsUmbrellaPlant") {};
	};
}
