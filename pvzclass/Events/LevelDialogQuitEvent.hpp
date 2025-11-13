#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 读档暂停对话框、游戏结束对话框退出关卡事件
	/// @note 冒险模式不会触发这个事件
	/// @param 触发事件时的 Dialog，Dialog 所在的 PVZApp
	/// @return 返回的页码，负数会被忽略。
	class LevelDialogQuitEvent
	{
	private:
		class Part1 : public DLLEventTemplate<0x433A0A, 6, REG_EDI, REG_ESI>
		{
		public:
			Part1(int address) : DLLEventTemplate() { Init(address); };
			virtual void InitExtra(AsmBuilder& builder)
			{
				builder.cmp_reg_imm(REG_EAX, 0).jl_rel(44);
				builder.mov_mem_esp_add_imm8_reg(0x1C, REG_EAX).popad().push_reg(REG_EAX);
				builder.invoke(0x44F380).mov_reg_mem_reg_add_imm32(REG_ESI, REG_ESI, 0x0C8).invoke(0x44FC30);
				builder.push_imm32(0x4338A0).ret();
			}
		}*part1;
		class Part2 : public DLLEventTemplate<0x457E7A, 6, REG_EDI, REG_ESI>
		{
		public:
			Part2(int address) : DLLEventTemplate() { Init(address); };
			virtual void InitExtra(AsmBuilder& builder)
			{
				builder.cmp_reg_imm(REG_EAX, 0).jl_rel(31);
				builder.mov_mem_esp_add_imm8_reg(0x1C, REG_EAX).popad().push_reg(REG_EAX);
				builder.mov_reg_mem_reg_add_imm32(REG_ESI, REG_ESI, 0x0C8).invoke(0x44FC30);
				builder.push_imm32(0x457F15).ret();
			}
		}*part2;
	public:
		LevelDialogQuitEvent() : LevelDialogQuitEvent("onPlantTakeDamage") {};
		LevelDialogQuitEvent(const char* name) : LevelDialogQuitEvent(PVZ::Memory::GetProcAddress(name)) {};
		LevelDialogQuitEvent(int address)
		{
			part1 = new Part1(address);
			part2 = new Part2(address);
		}
		void end()
		{
			part1->end();
			part2->end();
		}
	};
}
