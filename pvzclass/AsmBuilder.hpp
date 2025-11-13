#pragma once
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <iostream>

/// @brief 构建指令序列的类
class AsmBuilder
{
private:
	byte* code;
	int ptr;  // 指向最后一条指令的下一字节

public:
	AsmBuilder() : ptr(1)
	{
		code = new byte[64];
	}

	AsmBuilder(DWORD upper_limit) : ptr(1)
	{
		code = new byte[upper_limit];
	}

	~AsmBuilder()
	{
		delete[](code);
		code = nullptr;
	}

	// 返回当前生成的机器码
	byte* get_code() const
	{
		return code;
	}

	int get_length() const
	{
		return ptr;
	}

	// 浮点寄存器常量
	static const uint8_t F_ST0 = 0;
	static const uint8_t F_ST1 = 1;
	static const uint8_t F_ST2 = 2;
	static const uint8_t F_ST3 = 3;
	static const uint8_t F_ST4 = 4;
	static const uint8_t F_ST5 = 5;
	static const uint8_t F_ST6 = 6;
	static const uint8_t F_ST7 = 7;

	enum Reg8
	{
		REG_AL = 0,
		REG_CL,
		REG_DL,
		REG_BL,
		REG_AH,
		REG_CH,
		REG_DH,
		REG_BH,
	};

	// 添加一个字节到机器码中
	inline AsmBuilder& add_byte(uint8_t byte)
	{
		code[ptr++] = byte;
		return *this;
	}

	// 添加多个字节到机器码中（byte 数组形式）
	AsmBuilder& add_bytes(const uint8_t bytes[], const uint32_t length)
	{
		memcpy(code + ptr, bytes, length);
		ptr += length;
		return *this;
	}

	// 添加一个 DWORD (4 字节) 到机器码中
	inline AsmBuilder& add_dword(uint32_t dword)
	{
		*(int*)(code + ptr) = dword;
		ptr += 4;
		return *this;
	}

	// 添加一个 float (4 字节) 到机器码中
	inline AsmBuilder& add_float(float dword)
	{
		*(float*)(code + ptr) = dword;
		ptr += 4;
		return *this;
	}

	// 添加 NOP 指令
	AsmBuilder& nop()
	{
		return add_byte(0x90);
	}

	// 添加 PUSH 指令
	AsmBuilder& push(uint32_t value)
	{
		if (value <= 0x7F)
		{
			add_byte(0x6A);
			add_byte(static_cast<uint8_t>(value));
		}
		else
		{
			add_byte(0x68);
			add_dword(value);
		}
		return *this;
	}

	// 添加 PUSH 指令，操作数强制为 32 位
	AsmBuilder& push_imm32(uint32_t value)
	{
		return add_byte(0x68).add_dword(value);
	}

	// 添加 PUSH 指令
	AsmBuilder& push_reg(uint8_t reg)
	{
		if (reg > 7)
			throw std::invalid_argument("Invalid register for ADD");

		return add_byte(0x50 + reg);
	}

	AsmBuilder& push_float(float value)
	{
		return add_byte(0x68).add_float(value);
	}

	// 添加 PUSH 指令(地址)
	AsmBuilder& push_ptr(uint32_t address)
	{
		add_byte(0xFF);
		add_byte(0x35);
		add_dword(address);  // 添加 4 字节的内存地址
		return *this;
	}

	AsmBuilder& push_m32_esp_imm8(uint8_t offset)
	{
		return this->add_byte(0xFF).add_byte(0x74).add_byte(0x24).add_byte(offset);
	}

	// 添加 POP 指令
	AsmBuilder& pop(uint8_t reg)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for POP");
		}
		add_byte(0x58 + reg);
		return *this;
	}

	// 添加 POP PTR 指令（地址）
	AsmBuilder& pop_ptr(uint32_t address)
	{
		add_byte(0x8F);
		add_byte(0x05);
		add_dword(address);  // 添加目标内存地址
		return *this;
	}

	// 添加 MOV 指令（寄存器到寄存器）
	AsmBuilder& mov_reg_reg(uint8_t dest_reg, uint8_t src_reg)
	{
		if (dest_reg > 7 || src_reg > 7)
		{
			throw std::invalid_argument("Invalid register for MOV");
		}
		add_byte(0x8B);
		add_byte(0xC0 + (dest_reg << 3) + src_reg);
		return *this;
	}

	// 添加 MOV 指令
	AsmBuilder& mov_reg_imm(uint8_t reg, uint32_t value)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for MOV");
		}
		add_byte(0xB8 + reg);
		add_dword(value);
		return *this;
	}

	// 添加 MOV 指令（内存到寄存器）
	AsmBuilder& mov_reg_mem(uint8_t reg, uint32_t address)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for MOV");
		}
		add_byte(0x8B);
		add_byte(0x05 + (reg << 3));
		add_dword(address);
		return *this;
	}

	AsmBuilder& mov_reg_mem_reg_add_imm(uint8_t reg_dest, uint8_t reg_src, uint32_t imm)
	{
		if (reg_dest > 7 || reg_src > 7)
			throw std::invalid_argument("Invalid register for MOV");
		if (reg_src == REG_ESP)
			throw std::invalid_argument("This command is NOT suitable for esp");
		if (imm <= 0x7F)
			return this->add_byte(0x8B).add_byte(0x40 + (reg_dest << 3) + reg_src).add_byte(static_cast<uint8_t>(imm));
		else
			return this->add_byte(0x8B).add_byte(0x80 + (reg_dest << 3) + reg_src).add_dword(imm);
	}

	AsmBuilder& mov_reg_mem_reg_add_imm32(uint8_t reg_dest, uint8_t reg_src, uint32_t imm)
	{
		if (reg_dest > 7 || reg_src > 7)
			throw std::invalid_argument("Invalid register for MOV");
		if (reg_src == REG_ESP)
			throw std::invalid_argument("This command is NOT suitable for esp");
		return this->add_byte(0x8B).add_byte(0x80 + (reg_dest << 3) + reg_src).add_dword(imm);
	}

	AsmBuilder& mov_mem_esp_add_imm8_reg(uint8_t imm, uint8_t reg)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for MOV");
		}
		return this->add_byte(0x89).add_byte(0x44 + reg * 8).add_byte(0x24).add_byte(imm);
	}

	// 添加 MOV 指令（寄存器到内存）
	AsmBuilder& mov_mem_reg(uint32_t address, uint8_t reg)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for MOV");
		}
		add_byte(0x89);
		add_byte(0x05 + (reg << 3));
		add_dword(address);
		return *this;
	}

	// 添加 ADD 指令
	AsmBuilder& add_reg_reg(uint8_t dest_reg, uint8_t src_reg)
	{
		if (dest_reg > 7 || src_reg > 7)
		{
			throw std::invalid_argument("Invalid register for ADD");
		}
		add_byte(0x01);
		add_byte(0xC0 + (dest_reg << 3) + src_reg);
		return *this;
	}

	// 添加 ADD 指令（内存到寄存器）
	AsmBuilder& add_mem_reg(uint32_t address, uint8_t reg)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for ADD");
		}
		add_byte(0x03);
		add_byte(0x05 + (reg << 3));
		add_dword(address);
		return *this;
	}

	//添加 ADD 指令（寄存器到内存）
	AsmBuilder& add_reg_mem(uint8_t reg, uint32_t address)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for ADD");
		}
		add_byte(0x03);
		add_byte(0x05 + (reg << 3));
		add_dword(address);
		return *this;
	}

	//添加 ADD 指令 （数值到寄存器）
	AsmBuilder& add_reg_imm(uint8_t reg, uint32_t value)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for ADD");
		}
		if (value <= 0x7F)
		{
			add_byte(0x83);
			add_byte(0xC0 + reg);
			add_byte(static_cast<uint8_t>(value));
		}
		else
		{
			add_byte(0x81);
			add_byte(0xC0 + reg);
			add_dword(value);
		}
		return *this;
	}

	//添加 ADD 指令 （数值到内存）
	AsmBuilder& add_mem_imm(uint32_t address, uint32_t value)
	{
		if (value <= 0x7F)
		{
			add_byte(0xC6);
			add_byte(0x05);
			add_dword(address);
			add_byte(static_cast<uint8_t>(value));
		}
		else
		{
			add_byte(0xC7);
			add_byte(0x05);
			add_dword(address);
			add_dword(value);
		}
		return *this;
	}

	// 添加 SUB 指令
	AsmBuilder& sub_reg_reg(uint8_t dest_reg, uint8_t src_reg)
	{
		if (dest_reg > 7 || src_reg > 7)
		{
			throw std::invalid_argument("Invalid register for SUB");
		}
		add_byte(0x29);
		add_byte(0xC0 + (dest_reg << 3) + src_reg);
		return *this;
	}

	// 添加 SUB 指令（内存到寄存器）
	AsmBuilder& sub_mem_reg(uint32_t address, uint8_t reg)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for SUB");
		}
		add_byte(0x2B);
		add_byte(0x05 + (reg << 3));
		add_dword(address);
		return *this;
	}

	// 添加 SUB 指令（寄存器到内存）
	AsmBuilder& sub_reg_mem(uint8_t reg, uint32_t address)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for SUB");
		}
		add_byte(0x2B);
		add_byte(0x05 + (reg << 3));
		add_dword(address);
		return *this;
	}

	// 添加 SUB 指令 （数值到寄存器）
	AsmBuilder& sub_reg_imm(uint8_t reg, uint32_t value)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for SUB");
		}
		if (value <= 0x7F)
		{
			add_byte(0x83);
			add_byte(0xE8 + reg);
			add_byte(static_cast<uint8_t>(value));
		}
		else
		{
			add_byte(0x81);
			add_byte(0xE8 + reg);
			add_dword(value);
		}
		return *this;
	}

	// 添加 SUB 指令 （数值到内存）
	AsmBuilder& sub_mem_imm(uint32_t address, uint32_t value)
	{
		if (value <= 0x7F)
		{
			add_byte(0x80);
			add_byte(0x2D);
			add_dword(address);
			add_byte(static_cast<uint8_t>(value));
		}
		else
		{
			add_byte(0x81);
			add_byte(0x2D);
			add_dword(address);
			add_dword(value);
		}
		return *this;
	}

	// 添加 AND 指令
	AsmBuilder& and_reg_reg(uint8_t dest_reg, uint8_t src_reg)
	{
		if (dest_reg > 7 || src_reg > 7)
		{
			throw std::invalid_argument("Invalid register for AND");
		}
		add_byte(0x21);
		add_byte(0xC0 + (dest_reg << 3) + src_reg);
		return *this;
	}

	// 添加 AND 指令（内存到寄存器）
	AsmBuilder& and_mem_reg(uint32_t address, uint8_t reg)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for AND");
		}
		add_byte(0x23);
		add_byte(0x05 + (reg << 3));
		add_dword(address);
		return *this;
	}

	// 添加 AND 指令（寄存器到内存）
	AsmBuilder& and_reg_mem(uint8_t reg, uint32_t address)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for AND");
		}
		add_byte(0x23);
		add_byte(0x05 + (reg << 3));
		add_dword(address);
		return *this;
	}

	// 添加 AND 指令 （数值到寄存器）
	AsmBuilder& and_reg_imm(uint8_t reg, uint32_t value)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for AND");
		}
		if (value <= 0x7F)
		{
			add_byte(0x83);
			add_byte(0xE0 + reg);
			add_byte(static_cast<uint8_t>(value));
		}
		else
		{
			add_byte(0x81);
			add_byte(0xE0 + reg);
			add_dword(value);
		}
		return *this;
	}

	// 添加 AND 指令 （数值到内存）
	AsmBuilder& and_mem_imm(uint32_t address, uint32_t value)
	{
		if (value <= 0x7F)
		{
			add_byte(0x80);
			add_byte(0x25);
			add_dword(address);
			add_byte(static_cast<uint8_t>(value));
		}
		else
		{
			add_byte(0x81);
			add_byte(0x25);
			add_dword(address);
			add_dword(value);
		}
		return *this;
	}

	// 添加 OR 指令
	AsmBuilder& or_reg_reg(uint8_t dest_reg, uint8_t src_reg)
	{
		if (dest_reg > 7 || src_reg > 7)
		{
			throw std::invalid_argument("Invalid register for OR");
		}
		add_byte(0x09);
		add_byte(0xC0 + (dest_reg << 3) + src_reg);
		return *this;
	}

	// 添加 OR 指令（内存到寄存器）
	AsmBuilder& or_mem_reg(uint32_t address, uint8_t reg)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for OR");
		}
		add_byte(0x0B);
		add_byte(0x05 + (reg << 3));
		add_dword(address);
		return *this;
	}

	// 添加 OR 指令（寄存器到内存）
	AsmBuilder& or_reg_mem(uint8_t reg, uint32_t address)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for OR");
		}
		add_byte(0x0B);
		add_byte(0x05 + (reg << 3));
		add_dword(address);
		return *this;
	}

	// 添加 OR 指令 （数值到寄存器）
	AsmBuilder& or_reg_imm(uint8_t reg, uint32_t value)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for OR");
		}
		if (value <= 0x7F)
		{
			add_byte(0x83);
			add_byte(0xC8 + reg);
			add_byte(static_cast<uint8_t>(value));
		}
		else
		{
			add_byte(0x81);
			add_byte(0xC8 + reg);
			add_dword(value);
		}
		return *this;
	}

	// 添加 OR 指令 （数值到内存）
	AsmBuilder& or_mem_imm(uint32_t address, uint32_t value)
	{
		if (value <= 0x7F)
		{
			add_byte(0x80);
			add_byte(0x0D);
			add_dword(address);
			add_byte(static_cast<uint8_t>(value));
		}
		else
		{
			add_byte(0x81);
			add_byte(0x0D);
			add_dword(address);
			add_dword(value);
		}
		return *this;
	}

	// 添加 XOR 指令
	AsmBuilder& xor_reg_reg(uint8_t dest_reg, uint8_t src_reg)
	{
		if (dest_reg > 7 || src_reg > 7)
		{
			throw std::invalid_argument("Invalid register for XOR");
		}
		add_byte(0x31);
		add_byte(0xC0 + (dest_reg << 3) + src_reg);
		return *this;
	}

	// 添加 XOR 指令（内存到寄存器）
	AsmBuilder& xor_mem_reg(uint32_t address, uint8_t reg)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for XOR");
		}
		add_byte(0x33);
		add_byte(0x05 + (reg << 3));
		add_dword(address);
		return *this;
	}

	// 添加 XOR 指令（寄存器到内存）
	AsmBuilder& xor_reg_mem(uint8_t reg, uint32_t address)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for XOR");
		}
		add_byte(0x33);
		add_byte(0x05 + (reg << 3));
		add_dword(address);
		return *this;
	}

	// 添加 XOR 指令 （数值到寄存器）
	AsmBuilder& xor_reg_imm(uint8_t reg, uint32_t value)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for XOR");
		}
		if (value <= 0x7F)
		{
			add_byte(0x83);
			add_byte(0xF0 + reg);
			add_byte(static_cast<uint8_t>(value));
		}
		else
		{
			add_byte(0x81);
			add_byte(0xF0 + reg);
			add_dword(value);
		}
		return *this;
	}

	// 添加 XOR 指令 （数值到内存）
	AsmBuilder& xor_mem_imm(uint32_t address, uint32_t value)
	{
		if (value <= 0x7F)
		{
			add_byte(0x80);
			add_byte(0x35);
			add_dword(address);
			add_byte(static_cast<uint8_t>(value));
		}
		else
		{
			add_byte(0x81);
			add_byte(0x35);
			add_dword(address);
			add_dword(value);
		}
		return *this;
	}

	// 添加 CMP 指令
	AsmBuilder& cmp_reg_reg(uint8_t reg1, uint8_t reg2)
	{
		if (reg1 > 7 || reg2 > 7)
		{
			throw std::invalid_argument("Invalid register for CMP");
		}
		add_byte(0x39);
		add_byte(0xC0 + (reg1 << 3) + reg2);
		return *this;
	}

	// 添加 CMP 指令（内存到寄存器）
	AsmBuilder& cmp_mem_reg(uint32_t address, uint8_t reg)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for CMP");
		}
		add_byte(0x39);
		add_byte(0x05 + (reg << 3));
		add_dword(address);
		return *this;
	}

	// 添加 CMP 指令（寄存器到内存）
	AsmBuilder& cmp_reg_mem(uint8_t reg, uint32_t address)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for CMP");
		}
		add_byte(0x3B);
		add_byte(0x05 + (reg << 3));
		add_dword(address);
		return *this;
	}

	// 添加 CMP 指令 （数值到寄存器）
	AsmBuilder& cmp_reg_imm(uint8_t reg, uint32_t value)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for CMP");
		}
		if (value <= 0x7F)
		{
			add_byte(0x83);
			add_byte(0xF8 + reg);
			add_byte(static_cast<uint8_t>(value));
		}
		else
		{
			add_byte(0x81);
			add_byte(0xF8 + reg);
			add_dword(value);
		}
		return *this;
	}

	// 添加 CMP 指令 （数值到内存）
	AsmBuilder& cmp_mem_imm(uint32_t address, uint32_t value)
	{
		if (value <= 0x7F)
		{
			add_byte(0x80);
			add_byte(0x3D);
			add_dword(address);
			add_byte(static_cast<uint8_t>(value));
		}
		else
		{
			add_byte(0x81);
			add_byte(0x3D);
			add_dword(address);
			add_dword(value);
		}
		return *this;
	}

	AsmBuilder& test_al_al()
	{
		return this->add_byte(0x84).add_byte(0xC0);
	}

	// 添加 TEST 指令
	AsmBuilder& test_reg_reg(uint8_t reg1, uint8_t reg2)
	{
		if (reg1 > 7 || reg2 > 7)
		{
			throw std::invalid_argument("Invalid register for TEST");
		}
		add_byte(0x85);
		add_byte(0xC0 + (reg1 << 3) + reg2);
		return *this;
	}

	// 添加 TEST 指令（内存到寄存器）
	AsmBuilder& test_mem_reg(uint32_t address, uint8_t reg)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for TEST");
		}
		add_byte(0x85);
		add_byte(0x05 + (reg << 3));
		add_dword(address);
		return *this;
	}

	// 添加 TEST 指令（寄存器到内存）
	AsmBuilder& test_reg_mem(uint8_t reg, uint32_t address)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for TEST");
		}
		add_byte(0x85);
		add_byte(0x05 + (reg << 3));
		add_dword(address);
		return *this;
	}

	// 添加 TEST 指令 （数值到寄存器）
	AsmBuilder& test_reg_imm(uint8_t reg, uint32_t value)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for TEST");
		}
		if (value <= 0x7F)
		{
			add_byte(0xF7);
			add_byte(0xC0 + reg);
			add_byte(static_cast<uint8_t>(value));
		}
		else
		{
			add_byte(0xF7);
			add_byte(0xC0 + reg);
			add_dword(value);
		}
		return *this;
	}

	// 添加 TEST 指令 （数值到内存）
	AsmBuilder& test_mem_imm(uint32_t address, uint32_t value)
	{
		if (value <= 0x7F)
		{
			add_byte(0xF7);
			add_byte(0x25);
			add_dword(address);
			add_byte(static_cast<uint8_t>(value));
		}
		else
		{
			add_byte(0xF7);
			add_byte(0x25);
			add_dword(address);
			add_dword(value);
		}
		return *this;
	}

	// 添加 NOT 指令
	AsmBuilder& not_reg(Reg8 reg)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for NOT");
		}
		add_byte(0xF6);
		add_byte(0xD0 + reg);
		return *this;
	}

	// 添加 NOT 指令（内存）
	AsmBuilder& not_mem(uint32_t address)
	{
		add_byte(0xF7);
		add_byte(0x15);
		add_dword(address);
		return *this;
	}

	// 添加 NEG 指令
	AsmBuilder& neg_reg(Reg8 reg)
	{
		if (reg > 7)
		{
			throw std::invalid_argument("Invalid register for NEG");
		}
		add_byte(0xF6);
		add_byte(0xD8 + reg);
		return *this;
	}

	// 添加 JMP 指令
	AsmBuilder& jmp(uint32_t address)
	{
		add_byte(0xE9);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 JMP 指令（相对地址）
	AsmBuilder& jmp_rel(int32_t offset)
	{
		add_byte(0xE9);
		add_dword(offset);
		return *this;
	}

	// 添加 JMP 指令（相对地址），参数强制为 8 位
	AsmBuilder& jmp_rel8(int8_t offset)
	{
		return add_byte(0xEB).add_byte(offset);
	}

	// 添加 JZ 指令
	AsmBuilder& jz(uint32_t address)
	{
		add_byte(0x0F);
		add_byte(0x84);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 JZ 指令（相对地址）
	AsmBuilder& jz_rel(int32_t offset)
	{
		add_byte(0x0F);
		add_byte(0x84);
		add_dword(offset);
		return *this;
	}

	// 添加 JNZ 指令
	AsmBuilder& jnz(uint32_t address)
	{
		add_byte(0x0F);
		add_byte(0x85);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 JNZ 指令（相对地址）
	AsmBuilder& jnz_rel(int32_t offset)
	{
		add_byte(0x0F);
		add_byte(0x85);
		add_dword(offset);
		return *this;
	}

	// 添加 JE 指令
	AsmBuilder& je(uint32_t address)
	{
		return jz(address);
	}

	// 添加 JE 指令（相对地址）
	AsmBuilder& je_rel(int32_t offset)
	{
		return jz_rel(offset);
	}

	// 添加 JNE 指令
	AsmBuilder& jne(uint32_t address)
	{
		return jnz(address);
	}

	// 添加 JNE 指令（相对地址）
	AsmBuilder& jne_rel(int32_t offset)
	{
		return jnz_rel(offset);
	}

	// 添加 JB 指令
	AsmBuilder& jb(uint32_t address)
	{
		add_byte(0x0F);
		add_byte(0x82);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 JB 指令（相对地址）
	AsmBuilder& jb_rel(int32_t offset)
	{
		add_byte(0x0F);
		add_byte(0x82);
		add_dword(offset);
		return *this;
	}

	// 添加 JBE 指令
	AsmBuilder& jbe(uint32_t address)
	{
		add_byte(0x0F);
		add_byte(0x86);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 JBE 指令（相对地址）
	AsmBuilder& jbe_rel(int32_t offset)
	{
		add_byte(0x0F);
		add_byte(0x86);
		add_dword(offset);
		return *this;
	}

	// 添加 JA 指令
	AsmBuilder& ja(uint32_t address)
	{
		add_byte(0x0F);
		add_byte(0x87);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 JA 指令（相对地址）
	AsmBuilder& ja_rel(int32_t offset)
	{
		add_byte(0x0F);
		add_byte(0x87);
		add_dword(offset);
		return *this;
	}

	// 添加 JAE 指令
	AsmBuilder& jae(uint32_t address)
	{
		add_byte(0x0F);
		add_byte(0x83);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 JAE 指令（相对地址）
	AsmBuilder& jae_rel(int32_t offset)
	{
		add_byte(0x0F);
		add_byte(0x83);
		add_dword(offset);
		return *this;
	}

	// 添加 JC 指令
	AsmBuilder& jc(uint32_t address)
	{
		return jb(address);
	}

	// 添加 JC 指令（相对地址）
	AsmBuilder& jc_rel(int32_t offset)
	{
		return jb_rel(offset);
	}

	// 添加 JNC 指令
	AsmBuilder& jnc(uint32_t address)
	{
		return jae(address);
	}

	// 添加 JNC 指令（相对地址）
	AsmBuilder& jnc_rel(int32_t offset)
	{
		return jae_rel(offset);
	}

	// 添加 JS 指令
	AsmBuilder& js(uint32_t address)
	{
		add_byte(0x0F);
		add_byte(0x88);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 JS 指令（相对地址）
	AsmBuilder& js_rel(int32_t offset)
	{
		add_byte(0x0F);
		add_byte(0x88);
		add_dword(offset);
		return *this;
	}

	// 添加 JNS 指令
	AsmBuilder& jns(uint32_t address)
	{
		add_byte(0x0F);
		add_byte(0x89);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 JNS 指令（相对地址）
	AsmBuilder& jns_rel(int32_t offset)
	{
		add_byte(0x0F);
		add_byte(0x89);
		add_dword(offset);
		return *this;
	}

	// 添加 JP 指令
	AsmBuilder& jp(uint32_t address)
	{
		add_byte(0x0F);
		add_byte(0x8A);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 JP 指令（相对地址）
	AsmBuilder& jp_rel(int32_t offset)
	{
		add_byte(0x0F);
		add_byte(0x8A);
		add_dword(offset);
		return *this;
	}

	// 添加 JNP 指令
	AsmBuilder& jnp(uint32_t address)
	{
		add_byte(0x0F);
		add_byte(0x8B);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 JNP 指令（相对地址）
	AsmBuilder& jnp_rel(int32_t offset)
	{
		add_byte(0x0F);
		add_byte(0x8B);
		add_dword(offset);
		return *this;
	}

	// 添加 JO 指令
	AsmBuilder& jo(uint32_t address)
	{
		add_byte(0x0F);
		add_byte(0x80);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 JO 指令（相对地址）
	AsmBuilder& jo_rel(int32_t offset)
	{
		add_byte(0x0F);
		add_byte(0x80);
		add_dword(offset);
		return *this;
	}

	// 添加 JNO 指令
	AsmBuilder& jno(uint32_t address)
	{
		add_byte(0x0F);
		add_byte(0x81);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 JNO 指令（相对地址）
	AsmBuilder& jno_rel(int32_t offset)
	{
		add_byte(0x0F);
		add_byte(0x81);
		add_dword(offset);
		return *this;
	}

	// 添加 JG 指令
	AsmBuilder& jg(uint32_t address)
	{
		add_byte(0x0F);
		add_byte(0x8F);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 JG 指令（相对地址）
	AsmBuilder& jg_rel(int32_t offset)
	{
		add_byte(0x0F);
		add_byte(0x8F);
		add_dword(offset);
		return *this;
	}

	// 添加 JGE 指令
	AsmBuilder& jge(uint32_t address)
	{
		add_byte(0x0F);
		add_byte(0x8D);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 JGE 指令（相对地址）
	AsmBuilder& jge_rel(int32_t offset)
	{
		add_byte(0x0F);
		add_byte(0x8D);
		add_dword(offset);
		return *this;
	}

	// 添加 JL 指令
	AsmBuilder& jl(uint32_t address)
	{
		add_byte(0x0F);
		add_byte(0x8C);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 JL 指令（相对地址）
	AsmBuilder& jl_rel(int32_t offset)
	{
		add_byte(0x0F);
		add_byte(0x8C);
		add_dword(offset);
		return *this;
	}

	// 添加 JLE 指令
	AsmBuilder& jle(uint32_t address)
	{
		add_byte(0x0F);
		add_byte(0x8E);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 JLE 指令（相对地址）
	AsmBuilder& jle_rel(int32_t offset)
	{
		add_byte(0x0F);
		add_byte(0x8E);
		add_dword(offset);
		return *this;
	}

	// 添加 LOOP 指令
	AsmBuilder& loop(uint8_t count, uint32_t address)
	{
		if (count > 127)
		{
			throw std::invalid_argument("Invalid loop count for LOOP");
		}
		add_byte(0xE2);
		add_byte(count);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 LOOPZ 指令
	AsmBuilder& loopz(uint8_t count, uint32_t address)
	{
		if (count > 127)
		{
			throw std::invalid_argument("Invalid loop count for LOOPZ");
		}
		add_byte(0xE1);
		add_byte(count);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 LOOPNZ 指令
	AsmBuilder& loopnz(uint8_t count, uint32_t address)
	{
		if (count > 127)
		{
			throw std::invalid_argument("Invalid loop count for LOOPNZ");
		}
		add_byte(0xE0);
		add_byte(count);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 RET 指令
	AsmBuilder& ret()
	{
		add_byte(0xC3);
		return *this;
	}

	// 添加 RETN 指令
	AsmBuilder& retn(uint16_t count)
	{
		add_byte(0xC2);
		add_byte(static_cast<uint8_t>(count & 0xFF));
		add_byte(static_cast<uint8_t>((count >> 8) & 0xFF));
		return *this;
	}

	// 添加 INT3 指令
	AsmBuilder& int3()
	{
		add_byte(0xCC);
		return *this;
	}

	// 添加 CDQ 指令
	AsmBuilder& cdq()
	{
		add_byte(0x99);
		return *this;
	}

	// 添加 CLC 指令
	AsmBuilder& clc()
	{
		add_byte(0xF8);
		return *this;
	}

	// 添加 CLD 指令
	AsmBuilder& cld()
	{
		add_byte(0xFC);
		return *this;
	}

	// 添加 CMC 指令
	AsmBuilder& cmc()
	{
		add_byte(0xF5);
		return *this;
	}

	// 添加 STC 指令
	AsmBuilder& stc()
	{
		add_byte(0xF9);
		return *this;
	}

	// 添加 STD 指令
	AsmBuilder& std()
	{
		add_byte(0xFD);
		return *this;
	}

	// 添加 LAHF 指令
	AsmBuilder& lahf()
	{
		add_byte(0x9F);
		return *this;
	}

	// 添加 SAHF 指令
	AsmBuilder& sahf()
	{
		add_byte(0x9E);
		return *this;
	}

	// 添加 MOVZX 指令
	AsmBuilder& movzx_reg_mem(uint8_t dest_reg, uint8_t src_reg)
	{
		if (dest_reg > 7 || src_reg > 7)
		{
			throw std::invalid_argument("Invalid register for MOVZX");
		}
		add_byte(0x0F);
		add_byte(0xB6);
		add_byte(0x05 + (src_reg << 3) + dest_reg);
		return *this;
	}

	// 添加 MOVSX 指令
	AsmBuilder& movsx_reg_mem(uint8_t dest_reg, uint8_t src_reg)
	{
		if (dest_reg > 7 || src_reg > 7)
		{
			throw std::invalid_argument("Invalid register for MOVSX");
		}
		add_byte(0x0F);
		add_byte(0xBE);
		add_byte(0x05 + (src_reg << 3) + dest_reg);
		return *this;
	}

	// 添加 MOVSXD 指令
	AsmBuilder& movsxd_reg_mem(uint8_t dest_reg, uint8_t src_reg)
	{
		if (dest_reg > 7 || src_reg > 7)
		{
			throw std::invalid_argument("Invalid register for MOVSXD");
		}
		add_byte(0x63);
		add_byte(0x05 + (src_reg << 3) + dest_reg);
		return *this;
	}

	// 添加 CALL 指令
	AsmBuilder& call(uint32_t address)
	{
		add_byte(0xE8);
		add_dword(address - (ptr + 4));
		return *this;
	}

	// 添加 CALL 指令
	AsmBuilder& call_rel(uint32_t address)
	{
		add_byte(0xE8);
		add_dword(address);
		return *this;
	}

	// 添加 INVOKE 指令（绝对跳转）
	AsmBuilder& invoke(uint32_t address)
	{
		return this->call_rel(2).jmp_rel8(6).push_imm32(address).ret();
	}

	// 添加 INT 指令
	AsmBuilder& int_(uint8_t interrupt_number)
	{
		if (interrupt_number == 0x80)
		{
			add_byte(0xCD);
			add_byte(interrupt_number);
		}
		else
		{
			throw std::invalid_argument("Only INT 0x80 is supported");
		}
		return *this;
	}

	// 添加 LEA 指令
	AsmBuilder& lea_reg_mem(uint8_t dest_reg, uint32_t address)
	{
		if (dest_reg > 7)
		{
			throw std::invalid_argument("Invalid register for LEA");
		}
		add_byte(0x8D);
		add_byte(0x05 + (dest_reg << 3));
		add_dword(address);
		return *this;
	}

	// 添加 FNOP 指令
	AsmBuilder& fnop()
	{
		add_byte(0xD9);
		add_byte(0xD0);
		return *this;
	}
	// 添加 FLD 指令（加载浮点数到 ST0）
	AsmBuilder& fld(uint32_t address)
	{
		add_byte(0xD9);
		add_byte(0x05);
		add_dword(address);
		return *this;
	}
	// 添加 FST 指令（存储 ST0 到内存）
	AsmBuilder& fst(uint32_t address)
	{
		add_byte(0xD9);
		add_byte(0x15);
		add_dword(address);
		return *this;
	}
	// 添加 FSTP 指令（存储 ST0 到内存并弹出栈）
	AsmBuilder& fstp(uint32_t address)
	{
		add_byte(0xD9);
		add_byte(0x1D);
		add_dword(address);
		return *this;
	}
	AsmBuilder& fstp_m32_esp_imm8(uint8_t offset)
	{
		return this->add_byte(0xD9).add_byte(0x5C).add_byte(0x24).add_byte(offset);
	}
	AsmBuilder& fstp_ST(uint8_t index)
	{
		if (index > 7)
			throw std::invalid_argument("Invalid register for FSTP");
		return this->add_byte(0xDD).add_byte(0xDC + index);
	}
	// 添加 FILD 指令（加载整数到 ST0）
	AsmBuilder& fild(uint32_t address)
	{
		add_byte(0xDB);
		add_byte(0x05);
		add_dword(address);
		return *this;
	}
	// 添加 FIST 指令（存储 ST0 到整数内存）
	AsmBuilder& fist(uint32_t address)
	{
		add_byte(0xDB);
		add_byte(0x15);
		add_dword(address);
		return *this;
	}
	// 添加 FISTP 指令（存储 ST0 到整数内存并弹出栈）
	AsmBuilder& fistp(uint32_t address)
	{
		add_byte(0xDB);
		add_byte(0x1D);
		add_dword(address);
		return *this;
	}
	// 添加 FADD 指令（浮点加法）
	AsmBuilder& fadd(uint32_t address)
	{
		add_byte(0xD8);
		add_byte(0x05);
		add_dword(address);
		return *this;
	}
	// 添加 FSUB 指令（浮点减法）
	AsmBuilder& fsub(uint32_t address)
	{
		add_byte(0xD8);
		add_byte(0x25);
		add_dword(address);
		return *this;
	}
	// 添加 FMUL 指令（浮点乘法）
	AsmBuilder& fmul(uint32_t address)
	{
		add_byte(0xD8);
		add_byte(0x0D);
		add_dword(address);
		return *this;
	}
	// 添加 FDIV 指令（浮点除法）
	AsmBuilder& fdiv(uint32_t address)
	{
		add_byte(0xD8);
		add_byte(0x35);
		add_dword(address);
		return *this;
	}
	// 添加 FCOM 指令（浮点比较）
	AsmBuilder& fcom(uint32_t address)
	{
		add_byte(0xD8);
		add_byte(0x15);
		add_dword(address);
		return *this;
	}
	// 添加 FCOMP 指令（浮点比较并弹出栈）
	AsmBuilder& fcomp(uint32_t address)
	{
		add_byte(0xD8);
		add_byte(0x1D);
		add_dword(address);
		return *this;
	}
	// 添加 FLD1 指令（加载常数 1.0 到 ST0）
	AsmBuilder& fld1()
	{
		add_byte(0xD9);
		add_byte(0xE8);
		return *this;
	}
	// 添加 FLDL2T 指令（加载常数 log2(10) 到 ST0）
	AsmBuilder& fldl2t()
	{
		add_byte(0xD9);
		add_byte(0xE9);
		return *this;
	}
	// 添加 FLDL2E 指令（加载常数 log2(e) 到 ST0）
	AsmBuilder& fldl2e()
	{
		add_byte(0xD9);
		add_byte(0xEA);
		return *this;
	}
	// 添加 FLDPI 指令（加载常数 π 到 ST0）
	AsmBuilder& fldpi()
	{
		add_byte(0xD9);
		add_byte(0xEB);
		return *this;
	}
	// 添加 FLDLG2 指令（加载常数 log10(2) 到 ST0）
	AsmBuilder& fldlg2()
	{
		add_byte(0xD9);
		add_byte(0xEC);
		return *this;
	}
	// 添加 FLDLN2 指令（加载常数 ln(2) 到 ST0）
	AsmBuilder& fldln2()
	{
		add_byte(0xD9);
		add_byte(0xED);
		return *this;
	}
	// 添加 FLDZ 指令（加载常数 0.0 到 ST0）
	AsmBuilder& fldz()
	{
		add_byte(0xD9);
		add_byte(0xEE);
		return *this;
	}
	// 添加 FXCH 指令（交换 ST0 和 ST(i)）
	AsmBuilder& fxch(uint8_t st_reg)
	{
		if (st_reg > 7)
		{
			throw std::invalid_argument("Invalid floating-point register for FXCH");
		}
		add_byte(0xD9);
		add_byte(0xC8 + st_reg);
		return *this;
	}
	// 添加 FCHS 指令（改变 ST0 的符号）
	AsmBuilder& fchs()
	{
		add_byte(0xD9);
		add_byte(0xE0);
		return *this;
	}
	// 添加 FABS 指令（取 ST0 的绝对值）
	AsmBuilder& fabs()
	{
		add_byte(0xD9);
		add_byte(0xE1);
		return *this;
	}
	// 添加 FSQRT 指令（计算 ST0 的平方根）
	AsmBuilder& fsqrt()
	{
		add_byte(0xD9);
		add_byte(0xFA);
		return *this;
	}
	// 添加 FSIN 指令（计算 ST0 的正弦值）
	AsmBuilder& fsin()
	{
		add_byte(0xD9);
		add_byte(0xFE);
		return *this;
	}
	// 添加 FCOS 指令（计算 ST0 的余弦值）
	AsmBuilder& fcos()
	{
		add_byte(0xD9);
		add_byte(0xFF);
		return *this;
	}
	// 添加 FPTAN 指令（计算 ST0 的正切值）
	AsmBuilder& fptan()
	{
		add_byte(0xD9);
		add_byte(0xF2);
		return *this;
	}
	// 添加 FPATAN 指令（计算 ST1 / ST0 的反正切值）
	AsmBuilder& fpatan()
	{
		add_byte(0xD9);
		add_byte(0xF3);
		return *this;
	}
	// 添加 FRNDINT 指令（将 ST0 舍入为整数）
	AsmBuilder& frndint()
	{
		add_byte(0xD9);
		add_byte(0xFC);
		return *this;
	}
	// 添加 F2XM1 指令（计算 2^ST0 - 1）
	AsmBuilder& f2xm1()
	{
		add_byte(0xD9);
		add_byte(0xF0);
		return *this;
	}
	// 添加 FYL2X 指令（计算 ST1 * log2(ST0)）
	AsmBuilder& fyl2x()
	{
		add_byte(0xD9);
		add_byte(0xF1);
		return *this;
	}
	// 添加 FYL2XP1 指令（计算 ST1 * log2(ST0 + 1)）
	AsmBuilder& fyl2xp1()
	{
		add_byte(0xD9);
		add_byte(0xF9);
		return *this;
	}

	// 添加 PUSHAD 指令
	AsmBuilder& pushad()
	{
		return add_byte(PUSHAD);
	}
	// 添加 POPAD 指令
	AsmBuilder& popad()
	{
		return add_byte(POPAD);
	}
	// 退回 1 位或多位机器码
	AsmBuilder& back(const uint32_t count)
	{
		ptr -= count;
		if (ptr < 1)
			ptr = 1;
		return *this;
	}

	inline AsmBuilder& clear()
	{
		//code.clear();
		ptr = 1;
		code[1] = RET;
		return *this;
	}
};
