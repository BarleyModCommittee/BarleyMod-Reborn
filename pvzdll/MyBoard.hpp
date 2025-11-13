#pragma once
#include "framework.h"

constexpr int MAX_BOARD_ROWS = 6;

class MyBoard : public PVZ::Board
{
public:
	MyBoard(int address) : PVZ::Board(address) {};
	MyBoard(const PVZ::Board& board) : PVZ::Board(board.GetBaseAddress()) {};

	/// @brief 毒伤结算倒计时
	T_PROPERTY(uint8_t, PoisonCounter, __get_PoC, __set_PoC, 0x151);

	/// @brief 在指定行右侧生成一只指定类型的僵尸
	/// @param type 僵尸类型
	/// @param row 行
	/// @param from_wave 僵尸所在的波数
	/// @return 生成的僵尸
	PVZ::Zombie AddZombieInRow(ZombieType::ZombieType type, int row, int from_wave);
};