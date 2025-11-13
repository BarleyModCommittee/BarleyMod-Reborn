#pragma once
#include "../framework.h"

class MyPlant : public PVZ::Plant
{
public:
	MyPlant(int idoraddress) : PVZ::Plant(idoraddress) {};
	MyPlant(const PVZ::Plant& plant) : PVZ::Plant(plant.GetBaseAddress()) {};

	/// @brief 是否在 Board 上
	T_PROPERTY(mybool, OnBoard, __get_OnB, __set_OnB, 0x144);
};