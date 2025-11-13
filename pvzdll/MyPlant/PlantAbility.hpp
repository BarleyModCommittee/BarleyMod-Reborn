#pragma once
#include "MyPlant.hpp"
#include "../MyZombie/MyZombie.hpp"

namespace PlantAbility
{
	class BasePlant
	{
	public:
		/// @brief 植物完成原版的初始化过程后，执行此函数。
		/// @param plant 植物
		virtual void onCreated(MyPlant plant)
		{
			return;
		}
	};

	class PeaPlant : public BasePlant
	{
	public:
		void onCreated(MyPlant plant)
		{
			plant.ShootOrProductCountdown = plant.ShootOrProductCountdown * 150 / 100;
			plant.ShootOrProductInterval = 100;
		}
	};

	class PultPlant : public BasePlant
	{
	public:
		void onCreated(MyPlant plant)
		{
			plant.ShootOrProductCountdown = plant.ShootOrProductCountdown * 300 / 150;
			plant.ShootOrProductInterval = 150;
		}
	};
	typedef BasePlant* PlantPTR;
	PlantPTR GetAbility(SeedType::SeedType type);
}