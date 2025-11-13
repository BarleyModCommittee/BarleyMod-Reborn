#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	class Dialog_ButtonDepressEvent : public DLLEventTemplate<0x541044, 6, REG_EDX, REG_ECX>
	{
	public:
		Dialog_ButtonDepressEvent(int address) : DLLEventTemplate() { Init(address); };
		Dialog_ButtonDepressEvent(const char* name) : DLLEventTemplate() { Init(name); };
		Dialog_ButtonDepressEvent() : Dialog_ButtonDepressEvent("onLawnDialogButtonDepress") {};
	};
}
