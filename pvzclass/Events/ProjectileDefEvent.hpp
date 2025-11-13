#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 子弹对僵尸伤害类型
	enum ProjDmgType
	{
		/// @brief 非溅射伤害
		DAMAGE_SINGULAR,
		/// @brief 溅射伤害的主目标
		DAMAGE_SPLASH_PRIMARY,
		/// @brief 溅射伤害的次级目标
		DAMAGE_SPLASH_SECONDARY
	};

	/// @brief 子弹对僵尸造成伤害事件
	/// @param 依次为：子弹基址、受伤僵尸基址、伤害类型、溅射僵尸次级目标数、溅射伤害数值（非溅射时固定为 0）
	/// @return 调整后的伤害。负值会被忽略。
	class ProjectileDamageZombieEvent
	{
	private:
		class DamagePart1 : public IntDLLEventTemplate<0x46E073, 7, 0, 0,
			0, REG_EDX, false, CONST_VAL(0), CONST_VAL(0), CONST_VAL(DAMAGE_SINGULAR), REG_ESI, REG_EDI>
		{
		public:
			DamagePart1(const char* str) : IntDLLEventTemplate() { Init(str); };
			DamagePart1(int address) : IntDLLEventTemplate() { Init(address); };
		};
		class DamagePart2 : public DLLEvent
		{
		public:
			DamagePart2(int address)
			{
				hookAddress = 0x46D468;
				rawlen = 5;
				BYTE code[] =
				{
					PUSH_PTR_ESP_ADD_V(0x20),
					PUSH_PTR_ESP_ADD_V(0x3C),

					CALC_PTR_ESP_ADD_V_EUX(CALC_CMP, REG_ESI, 0x48),
					JNZ(4),
					PUSH(DAMAGE_SPLASH_PRIMARY),
					JMP(2),
					PUSH(DAMAGE_SPLASH_SECONDARY),

					PUSH_ESI,
					PUSH_EDI,
					INVOKE(address),
					ADD_ESP(0x14),

					TEST_EUX_EVX(REG_EAX, REG_EAX),
					JS(4),
					MOV_PTR_ESP_ADD_V_EUX(REG_EAX, 0x20),
				};
				start(STRING(code));
			}
			DamagePart2(const char* str) : DamagePart2(PVZ::Memory::GetProcAddress(str)) { };
		};
		DamagePart1* part1;
		DamagePart2* part2;
	public:
		ProjectileDamageZombieEvent()
		{
			const char* str = "onProjectileDamageZombie";
			part1 = new DamagePart1(str);
			part2 = new DamagePart2(str);
		}
		ProjectileDamageZombieEvent(int address)
		{
			part1 = new DamagePart1(address);
			part2 = new DamagePart2(address);
		}
		void end()
		{
			part1->end();
			part2->end();
		}
	};
}