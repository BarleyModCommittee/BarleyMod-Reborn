#include "pch.h"
#include "direct.h"

char working_dir[255];

void init()
{
	PVZ::Memory::localExecute = true;
	PVZ::Memory::DLLAddress = (int)GetModuleHandle(TEXT("BarleyMod.dll"));

	if (!PVZ::Memory::DLLAddress)
	{
		MessageBox(NULL, TEXT("改版模块加载失败！"), TEXT("Error"), MB_ICONERROR);
		exit(-1);
	}

	PVZ::Memory::Variable = PVZ::Memory::AllocMemory(4);

	_getcwd(working_dir, sizeof(working_dir));
	Creator::AsmInit();
}