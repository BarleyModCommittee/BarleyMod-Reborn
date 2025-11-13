#include "MyZombie.hpp"
#include "implement/index.hpp"

namespace ZombieAbility
{
	ZombiePTR pt_factory[] =
	{
		new BaseZombie(), new BaseZombie(), new BaseZombie(), new BaseZombie(), new BaseZombie(),
		new BaseZombie(), new BaseZombie(), new BaseZombie(), new BaseZombie(), new BaseZombie(),
		new BaseZombie(), new BaseZombie(), new BaseZombie(), new BaseZombie(), new BaseZombie(),
		new BaseZombie(), new BaseZombie(), new BaseZombie(), new BaseZombie(), new BaseZombie(),
		new BaseZombie(), new BaseZombie(), new BaseZombie(), new BaseZombie(), new BaseZombie(),

		new BaseZombie(), new BaseZombie(), new BaseZombie(), new BaseZombie(), new BaseZombie(),
		new BaseZombie(), new BaseZombie(), new BaseZombie()
	};
}

ZombieAbility::ZombiePTR ZombieAbility::GetAbility(ZombieType::ZombieType type)
{
	return ZombieAbility::pt_factory[type];
}