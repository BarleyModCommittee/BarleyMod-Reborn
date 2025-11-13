#pragma once
#include "DLLEvent.h"

/// @brief 模仿者即将生成新植物的事件。
/// @param 触发事件的模仿者（注意：不是即将生成的新植物）。
/// @return 是否继续结算该事件。
class ImitaterPlantEvent : public DLLEventTemplate<0x466B89, 6, REG_ESI>
{
public:
	ImitaterPlantEvent(const char* str) : DLLEventTemplate() { Init(str); };
	ImitaterPlantEvent(int address) : DLLEventTemplate() { Init(address); };
	ImitaterPlantEvent() : DLLEventTemplate() { Init("onLawnmowerUpdate"); };
};
