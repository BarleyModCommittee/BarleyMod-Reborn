#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	namespace Bungee
	{
		/// @brief 蹦极僵尸即将落地，准备判断保护伞的事件
		/// @param 触发事件的僵尸
		/// @return 若为负数，结算原版过程；否则表示弹飞僵尸的植物基址
		class LandStartEvent : public IntDLLEventTemplate<0x524FC1, 5, 0, 0, 0, REG_EAX, false, REG_EBP>
		{
		public:
			LandStartEvent(int address) : IntDLLEventTemplate() { Init(address); };
			LandStartEvent(const char* name) : IntDLLEventTemplate() { Init(name); };
			LandStartEvent() : LandStartEvent("onBungeeLandStart") {};
		};

		/// @brief 蹦极僵尸落地事件
		/// @param 触发事件的僵尸，僵尸手中的僵尸（可能为空）
		/// @return 是否强制执行滞留地面的效果
		class LandEvent : public DLLEvent
		{
		public:
			LandEvent(int address)
			{
				hookAddress = 0x5250C4;
				rawlen = 5;
				BYTE code[] =
				{
					INVOKE(0x41DE20),
					MOV_PTR_ESP_ADD_V_EUX(REG_EAX, 0x1C),
					PUSH_EAX,
					PUSH_EBP,
					INVOKE(address),
					ADD_ESP(8),

					TEST_EUX_EVX(REG_EAX, REG_EAX),
					JE(7),
					POPAD,
					PUSHDWORD(0x525109),
					RET,

					POPAD,
					JMP(6)
				};
				start(STRING(code));
			}
			LandEvent(const char* str) : LandEvent(PVZ::Memory::GetProcAddress(str)) {};
			LandEvent() : LandEvent("onBungeeLand") {};
		};
	}
}
