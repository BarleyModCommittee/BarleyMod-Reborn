#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	namespace PoleVaulter
	{
		/// @brief 撑杆僵尸完成跳跃事件
		/// @param 触发事件的僵尸
		class FullJumpEvent : public DLLEventTemplate<0x52601B, 8, REG_ESI>
		{
		public:
			FullJumpEvent(int address) : DLLEventTemplate() { Init(address); };
			FullJumpEvent(const char* name) : DLLEventTemplate() { Init(name); };
			FullJumpEvent() : FullJumpEvent("onPoleVaulterFullJump") {};
		};

		/// @brief 撑杆僵尸跳跃半段事件
		/// @param 触发事件的僵尸，僵尸将要越过的植物
		/// @return 是否继续结算原版过程（即高坚果技能）
		class HalfJumpEvent : public BoolDLLEventTemplate<0x525F9C, 6, 0x526015, REG_EAX, REG_ESI>
		{
		public:
			HalfJumpEvent(int address) : BoolDLLEventTemplate() { Init(address); };
			HalfJumpEvent(const char* name) : BoolDLLEventTemplate() { Init(name); };
			HalfJumpEvent() : HalfJumpEvent("onPoleVaulterHalfJump") {};
		};
		
		/// @brief 撑杆僵尸起跳事件
		/// @param 触发事件的僵尸，僵尸将要越过的植物
		class JumpStartEvent : public DLLEvent
		{
		public:
			JumpStartEvent(int address)
			{
				hookAddress = 0x525EF7;
				rawlen = 7;
				BYTE code[] =
				{
					FDIV_PTR_ESP_ADD_V(0x34),
					FSTP_PTR_EUX_ADD_V(REG_ESI, 0x34),
					PUSH_EDX,
					PUSH_ESI,
					INVOKE(address),
					ADD_ESP(8),
					POPAD,
					JMP(8)
				};
				start(STRING(code));
			}
			JumpStartEvent(const char* str) : JumpStartEvent(PVZ::Memory::GetProcAddress(str)) {};
			JumpStartEvent() : JumpStartEvent("onPoleVaultJumpStart") {};
		};
	}
}
