#include "TodParticleSystem.hpp"

PVZ::TodParticleSystem::TodParticleSystem(DWORD indexoraddress) : BaseClass(0)
{
	if (indexoraddress < 65536)
		BaseAddress = Memory::ReadPointer(0x6A9EC0, 0x820, 0, 0) + indexoraddress * 0x2C;
	else
		BaseAddress = indexoraddress;
}

AsmBuilder die_builder = AsmBuilder();
void PVZ::TodParticleSystem::Die()
{
	die_builder.clear()
		.push(this->BaseAddress)
		.invoke(0x5160C0)
		.ret();

	PVZ::Memory::Execute(die_builder);
}

AsmBuilder moveto_builder = AsmBuilder();
void PVZ::TodParticleSystem::MoveTo(float X, float Y)
{
	moveto_builder.clear()
		.push_float(Y)
		.push_float(X)
		.mov_reg_imm(REG_ESI, this->BaseAddress)
		.invoke(0x518440)
		.ret();

	PVZ::Memory::Execute(moveto_builder);
}

AsmBuilder color_builder = AsmBuilder();
void PVZ::TodParticleSystem::OverrideColor(const char* emitter_name, Color& color)
{
	DWORD tmp_ptr;
	if (emitter_name == nullptr)
	{
		tmp_ptr = 0;
	}
	else
	{
		tmp_ptr = PVZ::Memory::Variable + 100;
		PVZ::Memory::WriteArray<const char>(PVZ::Memory::Variable + 100, emitter_name, std::strlen(emitter_name) + 1);
	}

	color_builder.clear()
		.mov_reg_imm(REG_EBX, tmp_ptr)
		.push(color.Alpha)
		.push(color.Blue)
		.push(color.Green)
		.push(color.Red)
		.push_reg(REG_ESP)
		.push(this->BaseAddress)
		.invoke(0x518560)
		.add_reg_imm(REG_ESP, 16)
		.ret();

	PVZ::Memory::Execute(color_builder);
}

AsmBuilder additive_builder = AsmBuilder();
void PVZ::TodParticleSystem::OverrideExtraAdditiveDraw(bool isEnable)
{
	additive_builder.clear()
		.mov_reg_imm(REG_EDX, isEnable)
		.mov_reg_imm(REG_ESI, this->BaseAddress)
		.invoke(0x5185D0)
		.ret();

	PVZ::Memory::Execute(additive_builder);
}

AsmBuilder image_builder = AsmBuilder();
void PVZ::TodParticleSystem::OverrideImage(Image image)
{
	image_builder.clear()
		.mov_reg_imm(REG_ESI, image.GetBaseAddress())
		.mov_reg_imm(REG_EDX, this->BaseAddress)
		.invoke(0x518600)
		.ret();

	PVZ::Memory::Execute(image_builder);
}

AsmBuilder scale_builder = AsmBuilder();
void PVZ::TodParticleSystem::OverrideScale(float scale)
{
	scale_builder.clear()
		.push_float(scale)
		.mov_reg_imm(REG_EDX, this->BaseAddress)
		.invoke(0x518630)
		.ret();

	PVZ::Memory::Execute(scale_builder);
}

std::vector<PVZ::TodParticleSystem> PVZ::GetAllParticleSystem()
{
	std::vector<PVZ::TodParticleSystem> particle_syss;
	DWORD holder = PVZ::Memory::ReadPointer(0x6A9EC0, 0x820, 0);
	DWORD maxnum = Memory::ReadMemory<DWORD>(holder + 4), address = Memory::ReadMemory<DWORD>(holder);

	for (unsigned int i = 0; i < maxnum; i++)
	{
		PVZ::TodParticleSystem sys = PVZ::TodParticleSystem(address + i * 0x2C);
		if (!sys.Dead)
			particle_syss.push_back(sys);
	}

	return particle_syss;
}

AsmBuilder creator_builder = AsmBuilder();
PVZ::TodParticleSystem PVZ::CreateParticleSystem(float X, float Y, int render_order, EffectType::EffectType type)
{
	creator_builder.clear()
		.mov_reg_imm(REG_EAX, type)
		.mov_reg_imm(REG_ECX, render_order)
		.push_float(Y)
		.push_float(X)
		.mov_reg_imm(REG_EDX, PVZ_BASE)
		.invoke(0x453C80)
		.mov_mem_reg(PVZ::Memory::Variable, REG_EAX)
		.ret();

	return PVZ::TodParticleSystem(PVZ::Memory::Execute(creator_builder));
}
