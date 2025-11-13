#pragma once
#include "../framework.h"

class MyZombie : public PVZ::Zombie
{
public:
	MyZombie(int idoraddress) : PVZ::Zombie(idoraddress) {};
	MyZombie(const PVZ::Zombie& zombie) : PVZ::Zombie(zombie.GetBaseAddress()) {};
};