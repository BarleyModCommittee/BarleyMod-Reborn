#include "MyBoard.hpp"

PVZ::Zombie MyBoard::AddZombieInRow(ZombieType::ZombieType type, int row, int from_wave)
{
	return PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_EBX, from_wave)
		.push_imm32(row)
		.push_imm32(type)
		.mov_reg_imm(REG_EAX, this->BaseAddress)
		.invoke(0x40DDC0)
		.mov_mem_reg(PVZ::Memory::Variable, REG_EAX)
		.ret()
	);
}
