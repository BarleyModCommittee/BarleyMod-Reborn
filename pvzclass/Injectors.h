#pragma once
#include "PVZ.h"

/// @brief 代码注入类，可以注入 byte 数组形式的汇编码
class Injector
{
private:
	DWORD ReplaceRange, ReplacePos;
public:
	DWORD InjectPos, InjLen;
	/// @brief 构造一个注入器，并且在指定位置注入代码。
	/// @note 注入的代码依然需要以 RET 宏结尾。
	/// @note 跳转后的代码默认不保护现场，需要手动保护。
	/// @note 可以使用 RET 宏提前结束注入代码的运行。
	/// @param OriPTR 注入的地址
	/// @param OriLen 被替换的原始代码的长度
	/// @param ASMCode 注入的汇编码
	/// @param CodeLen 汇编码长度
	/// @param dropOri 是否弃掉原始代码。若为 false（默认值），则会在执行完注入代码后再执行被替换的代码。
	Injector(unsigned int OriPTR, int OriLen, byte* ASMCode, int CodeLen, bool dropOri = false)
	{
		ReplacePos = OriPTR;
		ReplaceRange = OriLen;
		InjectPos = PVZ::Memory::AllocMemory();
		InjLen = CodeLen;

		byte tmp[1024];
		PVZ::Memory::ReadArray<byte>(ReplacePos, tmp, OriLen);
		byte jmpout[6] =
		{
			PUSHDWORD(InjectPos),
			RET
		};
		PVZ::Memory::WriteArray<byte>(OriPTR, STRING(jmpout));
		for (int i = 0, tmpl = OriLen - 6; i < tmpl; i++)
			PVZ::Memory::WriteMemory<byte>(OriPTR + i + 6, NOP);

		PVZ::Memory::WriteArray<byte>(InjectPos, ASMCode, CodeLen);
		byte jmpback[6] =
		{
			PUSHDWORD(OriPTR + OriLen),
			RET
		};
		if (dropOri)
		{
			PVZ::Memory::WriteArray<byte>(InjectPos + InjLen, STRING(jmpback));
			InjLen += 6;
			PVZ::Memory::WriteArray<byte>(InjectPos + InjLen, tmp, OriLen);
		}
		else
		{
			PVZ::Memory::WriteArray<byte>(InjectPos + InjLen, tmp, OriLen);
			PVZ::Memory::WriteArray<byte>(InjectPos + InjLen + OriLen, STRING(jmpback));
		}

		return;
	}
	/// @brief 析构函数。会自动调用 Remove() 方法。
	/// @see Remove()
	~Injector()
	{
		this->Remove();
		return;
	}
	/// @brief 消除该 Injector 产生的效应。
	inline void Remove()
	{
		if (InjectPos == -1)
			return;
		byte tmp[1024];
		PVZ::Memory::ReadArray<byte>(InjectPos + InjLen, tmp, ReplaceRange);
		PVZ::Memory::WriteArray<byte>(ReplacePos, tmp, ReplaceRange);
		PVZ::Memory::FreeMemory(InjectPos);
		return;
	}
};