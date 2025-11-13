#include "../PVZ.h"
#include "../Const.h"
#include "GameObject.hpp"
#include "LawnMower.hpp"
#include "Griditem.hpp"
#include "Mouse.hpp"
#include "Advice.hpp"
#include "SeedBank.hpp"
#include "Challenge.hpp"

PVZ::Board PVZ::GetBoard()
{
	int address = PVZBASEADDRESS;
	return (address == 0 ? INVALID_BASEADDRESS : Board(address));
}

void PVZ::Board::SetMemSize(int NewSize)
{
	if (NewSize < 0x57B0)
		return;
	PVZ::Memory::WriteMemory<int>(0x44F60F, NewSize);
	PVZ::Memory::WriteMemory<int>(0x4819E1, NewSize - 0x164);
}

PVZ::PVZApp PVZ::Board::GetPVZApp()
{
	return PVZApp(Memory::ReadMemory<DWORD>(BaseAddress + 0x8C));
}

int PVZ::Board::GetGridFog(int row, int column)
{
	if (row < 0 || row > 6 || column < 0 || column > 8)
		return(0);
	return(Memory::ReadMemory<int>(BaseAddress + 4 * row + 0x1C * column));
}

void PVZ::Board::GetZombieAllowed(ZombieType::ZombieType* ztypes)
{
	int p = 0;
	for (int i = 0; i < 33; i++)
	{
		if (Memory::ReadMemory<byte>(BaseAddress + 0x54D4 + i))
		{
			ztypes[p] = ZombieType::ZombieType(i);
			p++;
		}
	}
}

int PVZ::Board::__get_WaveCount()
{
	return Memory::ReadMemory<int>(BaseAddress + 0x5564);
}

void PVZ::Board::__set_WaveCount(int value)
{
	if (value >= 0 && value <= WaveCount)
	{
		Memory::WriteMemory<int>(BaseAddress + 0x5564, value);
		Memory::WriteMemory<int>(BaseAddress + 0x5610, value * 150 / WaveCount);
	}
}

SceneType::SceneType PVZ::Board::__get_LevelScene()
{
	return Memory::ReadMemory<SceneType::SceneType>(BaseAddress + 0x554C);
}

void PVZ::Board::__set_LevelScene(SceneType::SceneType value)
{
	Memory::WriteMemory<SceneType::SceneType>(BaseAddress + 0x554C, value);
	SETARG(__asm__set__LevelScene, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__set__LevelScene));
}

int PVZ::Board::GridToXPixel(int row, int column)
{
	PVZLevel::PVZLevel mode = Memory::ReadMemory<PVZLevel::PVZLevel>(Memory::ReadMemory<int>(this->BaseAddress + 0x8C) + 0x7F8);
	if (mode == PVZLevel::Zen_Garden)
	{
		SceneType::SceneType scene = this->LevelScene;
		if (scene == SceneType::Aquarium || scene == SceneType::MushroomGarden || scene == SceneType::ZenGarden)
			return(Const::GetZenGardenXPixel(row, column, scene));
	}
	return(80 * column + 40);
}

int PVZ::Board::GridToYPixel(int row, int column)
{
	PVZLevel::PVZLevel mode = Memory::ReadMemory<PVZLevel::PVZLevel>(Memory::ReadMemory<int>(this->BaseAddress + 0x8C) + 0x7F8);
	SceneType::SceneType scene = this->LevelScene;
	if (mode == PVZLevel::Zen_Garden)
	{
		if (scene == SceneType::Aquarium || scene == SceneType::MushroomGarden || scene == SceneType::ZenGarden)
			return(Const::GetZenGardenYPixel(row, column, scene));
	}
	if(scene == SceneType::Roof || scene == SceneType::MoonNight)
	{
		int offset = 0;
		if (column < 5)
			offset = 20 * (5 - column);
		return(85 * row + offset + 70);
	}
	if (scene == SceneType::Pool || scene == SceneType::Fog)
		return(85 * row + 80);
	return(100 * row + 80);
}

void PVZ::Board::Lose()
{
	PVZ::PVZApp pvz = this->GetPVZApp();
	if (pvz.LevelId == PVZLevel::Zombiguarium || (pvz.LevelId >= 61 && pvz.LevelId <= 70))
	{
		SETARG(__asm__Lose, 3) = this->BaseAddress;
		Memory::Execute(STRING(__asm__Lose));
	}
	else
		pvz.GameState = PVZGameState::Losing;
}

byte __asm__Board_TakeSunMoney[] =
{
	MOV_EBX(0),
	MOV_EDI(0),
	INVOKE(0x41BA60),
	MOV_PTR_ADDR_EAX(0),
	RET
};

bool PVZ::Board::TakeSunMoney(int amount)
{
	SETARG(__asm__Board_TakeSunMoney, 1) = amount;
	SETARG(__asm__Board_TakeSunMoney, 6) = this->BaseAddress;
	SETARG(__asm__Board_TakeSunMoney, 24) = PVZ::Memory::Variable;
	return(static_cast<bool>(Memory::Execute(STRING(__asm__Board_TakeSunMoney))));
}

void PVZ::Board::Win()
{
	SETARG(__asm__Win, 1) = this->BaseAddress;
	PVZ::PVZApp pvz = this->GetPVZApp();
	if (pvz.LevelId > 0 && pvz.LevelId < 16)
	{
		if (pvz.GameState == PVZGameState::Playing)
			Memory::Execute(STRING(__asm__Win));
	}
	else Memory::Execute(STRING(__asm__Win));
}

byte __asm__Save[] =
{
	PUSHDWORD(0),
	MOV_ECX(0),
	INVOKE(0x404450),
	PUSH_EAX,
	MOV_EDI(0),
	INVOKE(0x4820D0),
	MOV_PTR_ADDR_EAX(0),
	ADD_ESP(4),
	RET
};

bool PVZ::Board::Save(const char* path, int pathlen)
{
	PVZ::Memory::WriteArray<const char>(PVZ::Memory::Variable + 100, path, pathlen);
	SETARG(__asm__Save, 1) = PVZ::Memory::Variable + 100;
	SETARG(__asm__Save, 6) = PVZ::Memory::Variable + 600;
	SETARG(__asm__Save, 25) = BaseAddress;
	SETARG(__asm__Save, 43) = PVZ::Memory::Variable;
	return PVZ::Memory::Execute(STRING(__asm__Save)) & 1;
}

byte __asm__Load[] =
{
	PUSHDWORD(0),
	MOV_ECX(0),
	INVOKE(0x404450),
	PUSH_EAX,
	MOV_ECX(0),
	INVOKE(0x481FE0),
	MOV_PTR_ADDR_EAX(0),
	ADD_ESP(4),
	RET
};

bool PVZ::Board::Load(const char* path, int pathlen)
{
	PVZ::Memory::WriteArray<const char>(PVZ::Memory::Variable + 100, path, pathlen);
	SETARG(__asm__Load, 1) = PVZ::Memory::Variable + 100;
	SETARG(__asm__Load, 6) = PVZ::Memory::Variable + 600;
	SETARG(__asm__Load, 25) = BaseAddress;
	SETARG(__asm__Load, 43) = PVZ::Memory::Variable;
	return PVZ::Memory::Execute(STRING(__asm__Load)) & 1;
}

void PVZ::Board::Assault(int countdown)
{
	Memory::WriteMemory<int>(BaseAddress + 0x5574, countdown);
}

void PVZ::Board::Bell(int countdown)
{
	Memory::WriteMemory<int>(BaseAddress + 0x5750, countdown);
}

void PVZ::Board::Earthquake(int horizontalAmplitude, int verticalAmplitude, int duration)
{
	Memory::WriteMemory<int>(BaseAddress + 0x5540, duration);
	Memory::WriteMemory<int>(BaseAddress + 0x5544, horizontalAmplitude);
	Memory::WriteMemory<int>(BaseAddress + 0x5548, verticalAmplitude);
}

PVZ::Lawn PVZ::Board::GetLawn()
{
	return Lawn(BaseAddress);
}

PVZ::Icetrace PVZ::Board::GetIcetrace()
{
	return Icetrace(BaseAddress);
}

PVZ::Wave PVZ::Board::GetWave(int index)
{
	if (index >= 0 && index <= this->WaveCount)
		return Wave(BaseAddress + 0x6B4 + index * 200);
	else
		return Wave(0);
}

PVZ::MousePointer PVZ::Board::GetMousePointer()
{
	return MousePointer(BaseAddress);
}

PVZ::Caption PVZ::Board::GetCaption()
{
	return Caption(BaseAddress);
}

PVZ::CardSlot PVZ::Board::GetCardSlot()
{
	return CardSlot(BaseAddress);
}

PVZ::Challenge PVZ::Board::GetMiscellaneous()
{
	return this->GetChallenge<PVZ::Challenge>();
}
