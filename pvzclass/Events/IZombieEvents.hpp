#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief IZE 关主题植物初始化事件
	/// @param 触发事件的 Challenge
	/// @return 是否初始化植物
	class IZESetupThemeEvent : public BoolDLLEventTemplate<0x42B041, 5, 0x42B277, REG_EDI>
	{
	public:
		IZESetupThemeEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		IZESetupThemeEvent(const char* name) : BoolDLLEventTemplate() { Init(name); };
		IZESetupThemeEvent() : IZESetupThemeEvent("onIZESetupTheme") {};
	};

	/// @brief 判断当前关卡是否为 IZ 关卡的事件
	/// @param 触发事件的 PVZApp
	/// @return 若为负数，则按原版处理；若为 0，则为非 IZ 关卡；若为正数，则为 IZ 关卡。
	class IsIZEvent
	{
	private:
		class Part1 : public IntDLLEventTemplate<0x4537DC, 6, 0, 0, 0, REG_EAX, true, REG_EAX>
		{
		public:
			Part1(int address) : IntDLLEventTemplate() { Init(address); };
		} *part1;
		class Part2 : public DLLEventTemplate<0x41F5AB, 6, REG_EAX>
		{
		public:
			Part2(int address) : DLLEventTemplate() { Init(address); };
			virtual void InitExtra(AsmBuilder& builder)
			{
				builder.test_al_al().js_rel(16).je_rel(7);
				builder.popad().push_imm32(0x41F5E3).ret();
				builder.popad().push_imm32(0x41F5E9).ret();
			}
		} *part2;
		class Part3 : public DLLEventTemplate<0x4200D6, 6, REG_EAX>
		{
		public:
			Part3(int address) : DLLEventTemplate() { Init(address); };
			virtual void InitExtra(AsmBuilder& builder)
			{
				builder.test_al_al().js_rel(20).je_rel(7);
				builder.popad().push_imm32(0x42010E).ret();
				builder.popad().push_imm32(0x420114).ret();
			}
		} *part3;
		class Part4 : public ThreeStateEventTemplate<0x461E81, 6, 0x461EB9, 0x461F07, REG_ECX>
		{
		public:
			Part4(int address) : ThreeStateEventTemplate() { Init(address); };
		} *part4;
	public:
		IsIZEvent() : IsIZEvent("IsIZ") {};
		IsIZEvent(const char* name) : IsIZEvent(PVZ::Memory::GetProcAddress(name)) {};
		IsIZEvent(int address)
		{
			part1 = new Part1(address);
			part2 = new Part2(address);
			part3 = new Part3(address);
			part4 = new Part4(address);
		}
		void end()
		{
			part1->end();
			part2->end();
			part3->end();
			part4->end();
		}
	};

	/// @brief 判断当前关卡是否为 IZE 关卡的事件，仅判定 IZE 独有而其他 IZ 关没有的特性。
	/// @param 触发事件的 LevelID
	/// @return 是否为 IZE 关卡
	/// @todo 检查每三轮过关奖励的条件分析是否正确
	class IsIZEEvent
	{
	private:
		class Part1 : public DLLEventTemplate<0x42993F, 10, REG_EAX>
		{
		protected:
			virtual void InitExtra(AsmBuilder& builder)
			{
				builder.test_al_al().popad().mov_reg_imm(REG_ECX, 1).jz_rel(6)
					.push_imm32(0x429949).ret()
					.push_imm32(0x42995D).ret();
			}
		public:
			Part1(int address) : DLLEventTemplate() { Init(address); };
		} *p1;
		class Part2 : public DiversionEventTemplate<0x42AF3D, 9, 0x42AF46, 0x42B277, REG_EAX>
		{
		public:
			Part2(int address) : DiversionEventTemplate() { Init(address); };
		} *p2;
		class Part3 : public DiversionEventTemplate<0x42A718, 5, 0x42A71D, 0x42A725, REG_EAX>
		{
		public:
			Part3(int address) : DiversionEventTemplate() { Init(address); };
		} *p3;
		class Part4 : public DiversionEventTemplate<0x4255D7, 5, 0x4255DC, 0x4255E1, REG_ESI>
		{
		public:
			Part4(int address) : DiversionEventTemplate() { Init(address); };
		} *p4;
		class Part5 : public DiversionEventTemplate<0x4253E9, 5, 0x4253EE, 0x425402, REG_EAX>
		{
		public:
			Part5(int address) : DiversionEventTemplate() { Init(address); };
		} *p5;
		class Part6 : public DiversionEventTemplate<0x41BFBE, 5, 0x41BFC3, 0x41BFCA, REG_EAX>
		{
		public:
			Part6(int address) : DiversionEventTemplate() { Init(address); };
		} *p6;
		class Part7 : public DiversionEventTemplate<0x40B6F1, 9, 0x40B6FA, 0x40B7CC, REG_EDX>
		{
		public:
			Part7(int address) : DiversionEventTemplate() { Init(address); };
		} *p7;
		class Part8 : public DiversionEventTemplate<0x42EEA7, 9, 0x42EFEA, 0x42EEB0, REG_EDI>
		{
		public:
			Part8(int address) : DiversionEventTemplate() { Init(address); };
		} *p8;
		class Part9 : public DiversionEventTemplate<0x45415C, 5, 0x45412A, 0x454161, REG_EAX>
		{
		public:
			Part9(int address) : DiversionEventTemplate() { Init(address); };
		} *p9;
		class Part10 : public DiversionEventTemplate<0x43155D, 5, 0x431578, 0x431562, REG_EDX>
		{
		public:
			Part10(int address) : DiversionEventTemplate() { Init(address); };
		} *p10;
		class Part11 : public DiversionEventTemplate<0x4320AC, 5, 0x4320B6, 0x4320B1, REG_EDI>
		{
		public:
			Part11(int address) : DiversionEventTemplate() { Init(address); };
		} *p11;
		class Part12 : public DiversionEventTemplate<0x4304E3, 9, 0x4306C4, 0x4304EC, REG_EAX>
		{
		public:
			Part12(int address) : DiversionEventTemplate() { Init(address); };
		} *p12;
		class Part13 : public DLLEvent
		{
		public:
			Part13(int address)
			{
				hookAddress = 0x42B8FC;
				rawlen = 7;
				BYTE code[] =
				{
					PUSH_PTR_EUX_ADD(REG_ECX, 0x7F8), INVOKE(address), ADD_ESP(4),

					TEST_AL_AL,
					POPAD,
					JE(6),

					PUSHDWORD(0x42B905),
					RET,

					PUSHDWORD(0x42B914),
					RET,
				};
				start(STRING(code));
			}
		} *p13;
		class Part14 : public DiversionEventTemplate<0x4133A2, 5, 0x4133A7, 0x4133F4, REG_EAX>
		{
		public:
			Part14(int address) : DiversionEventTemplate() { Init(address); };
		} *p14;
		class Part15 : public DiversionEventTemplate<0x40C0D7, 5, 0x40C0DC, 0x40C0FF, REG_ESI>
		{
		public:
			Part15(int address) : DiversionEventTemplate() { Init(address); };
		} *p15;
		class Part16 : public DiversionEventTemplate<0x40C7CD, 9, 0x40C7D6, 0x40C86E, REG_EBP>
		{
		public:
			Part16(int address) : DiversionEventTemplate() { Init(address); };
		} *p16;
		class Part17 : public DiversionEventTemplate<0x40C4A7, 9, 0x40C595, 0x40C4B0, REG_EAX>
		{
		public:
			Part17(int address) : DiversionEventTemplate() { Init(address); };
		} *p17;
		class Part18 : public DiversionEventTemplate<0x417EFE, 5, 0x417F23, 0x417F03, REG_EAX>
		{
		public:
			Part18(int address) : DiversionEventTemplate() { Init(address); };
		} *p18;
		class Part19 : public DiversionEventTemplate<0x4136D2, 5, 0x4136F5, 0x4136D7, REG_EAX>
		{
		public:
			Part19(int address) : DiversionEventTemplate() { Init(address); };
		} *p19;
	public:
		IsIZEEvent() : IsIZEEvent("IsIZE") {};
		IsIZEEvent(const char* name) : IsIZEEvent(PVZ::Memory::GetProcAddress(name)) {};
		IsIZEEvent(int address)
		{
			p1 = new Part1(address);
			p2 = new Part2(address);
			p3 = new Part3(address);
			p4 = new Part4(address);
			p5 = new Part5(address);
			p6 = new Part6(address);
			p7 = new Part7(address);
			p8 = new Part8(address);
			p9 = new Part9(address);
			p10 = new Part10(address);
			p11 = new Part11(address);
			p12 = new Part12(address);
			p13 = new Part13(address);
			p14 = new Part14(address);
			p15 = new Part15(address);
			p16 = new Part16(address);
			p17 = new Part17(address);
			p18 = new Part18(address);
			p19 = new Part19(address);
		}
		void end()
		{
			p1->end();
			p2->end();
			p3->end();
			p4->end();
			p5->end();
			p6->end();
			p7->end();
			p8->end();
			p9->end();
			p10->end();
			p11->end();
			p12->end();
			p13->end();
			p14->end();
			p15->end();
			p16->end();
			p17->end();
			p18->end();
			p19->end();
		}
	};

	/// @brief IZ 关卡发送初始字幕的事件。
	/// @param 触发事件的 Challenge
	/// @return 是否显示原生的字幕。
	class IZStartAdviceEvent : BoolDLLEventTemplate<0x42B290, 7, 0x42B330, MEM_ESP_ADD(0x20)>
	{
	public:
		IZStartAdviceEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		IZStartAdviceEvent(const char* name) : BoolDLLEventTemplate() { Init(name); };
		IZStartAdviceEvent() : IZStartAdviceEvent("onIZStartAdvice") {};
	};

	/// @brief IZ 中放置僵尸事件
	/// @param 触发事件的 Zombie
	class IZPlaceZombieEvent : public DLLEventTemplate<0x42A42A, 9, REG_EAX>
	{
	public:
		IZPlaceZombieEvent(int address) : DLLEventTemplate() { Init(address); };
		IZPlaceZombieEvent(const char* name) : DLLEventTemplate() { Init(name); };
		IZPlaceZombieEvent() : IZPlaceZombieEvent("onIZPlaceZombie") {};
	};

	/// @brief 判断 IZ 关卡失败条件事件
	/// @param 触发事件时场上的总阳光数
	/// @return 阳光是否足够使用僵尸卡牌
	class IZSunConditionEvent : public DiversionEventTemplate<0x42B4B3, 7, 0x42B526, 0x42B4BA, MEM_ESP_ADD(0x30)>
	{
	public:
		IZSunConditionEvent(int address) : DiversionEventTemplate() { Init(address); };
		IZSunConditionEvent(const char* name) : DiversionEventTemplate() { Init(name); };
		IZSunConditionEvent() : IZSunConditionEvent("IsSunSuffcient") {};
	};
}
