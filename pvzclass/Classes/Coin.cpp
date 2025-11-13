#include "GameObject.hpp"

PVZ::Coin::Coin(int indexoraddress)
{
	if (indexoraddress > 1024)
		BaseAddress = indexoraddress;
	else
		BaseAddress = Memory::ReadMemory<int>(PVZBASEADDRESS + 0xE4) + indexoraddress * 0xD8;
}

void PVZ::Coin::GetCollision(PVZ::Rect* collbox)
{
	collbox->X = NULL;
	collbox->Y = NULL;
	collbox->Width = Memory::ReadMemory<int>(BaseAddress + 0x10);
	collbox->Height = Memory::ReadMemory<int>(BaseAddress + 0x14);
}

void PVZ::Coin::SetCollision(PVZ::Rect* collbox)
{
	Memory::WriteMemory<int>(BaseAddress + 0x10, collbox->Width);
	Memory::WriteMemory<int>(BaseAddress + 0x14, collbox->Height);
}

PVZ::Attachment PVZ::Coin::GetAttachment()
{
	int ID = Memory::ReadMemory<int>(BaseAddress + 0x60);
	return (((ID & 0xFFFF0000) == 0) ? INVALID_BASEADDRESS : Attachment(ID & 0x00FFFF));
}

PVZ::GardenPlant PVZ::Coin::GetGardenPlant()
{
	return PVZ::GardenPlant(this->BaseAddress + 0x68);
}

void PVZ::Coin::Collect()
{
	SETARG(__asm__Collect, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Collect));
}

byte __asm__Coin_die[] =
{
	MOV_ESI(0),
	INVOKE(0x432DD0),
	RET
};

void PVZ::Coin::Die()
{
	SETARG(__asm__Coin_die, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Coin_die));
}