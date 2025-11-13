#include "Dialog.hpp"

void PVZ::Dialog::CalcSize(int ExtraX, int ExtraY)
{
	PVZ::Memory::Execute(AsmBuilder()
		.push_imm32(ExtraY)
		.push_imm32(ExtraX)
		.mov_reg_imm(REG_ESI, this->GetBaseAddress())
		.invoke(0x456F30)
		.ret()
	);
}