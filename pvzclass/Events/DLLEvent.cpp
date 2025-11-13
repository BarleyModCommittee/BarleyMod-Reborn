#include "DLLEvent.h"

int DLLEvent::newAddress = 0;

void DLLEvent::start(BYTE* code, int newlen)
{
	if (newAddress == 0) newAddress = PVZ::Memory::AllocMemory(16, 0);
	rawCode = new BYTE[rawlen];
	PVZ::Memory::ReadArray<BYTE>(hookAddress, rawCode, rawlen);
	if (rawCode[0] == 0xE8 || rawCode[0] == 0xE9)
		SETARG(rawCode, 1) = SETARG(rawCode, 1) + hookAddress - newAddress - newlen - 2;
	BYTE jmpto[] = { JMPFAR(newAddress - (hookAddress + 5)) };
	PVZ::Memory::WriteArray<BYTE>(hookAddress, jmpto, 5);
	for (int i = 5; i < rawlen; i++) PVZ::Memory::WriteMemory<BYTE>(hookAddress + i, NOP);
	BYTE jmpback[] = { JMPFAR(hookAddress - (newAddress + newlen + 7)) };
	PVZ::Memory::WriteMemory<BYTE>(newAddress, PUSHAD);
	PVZ::Memory::WriteArray<BYTE>(newAddress + 1, code, newlen);
	PVZ::Memory::WriteMemory<BYTE>(newAddress + newlen + 1, POPAD);
	PVZ::Memory::WriteArray<BYTE>(newAddress + newlen + 2, rawCode, rawlen);
	PVZ::Memory::WriteArray<BYTE>(newAddress + newlen + rawlen + 2, jmpback, 5);
	newAddress += newlen + rawlen + 0x10;
}

void DLLEvent::end()
{
	PVZ::Memory::WriteArray<BYTE>(hookAddress, rawCode, rawlen);
	PVZ::Memory::FreeMemory(newAddress);
}
