#pragma once
#include "../PlantAbility.hpp"

namespace PlantAbility
{
	class Cactus : public BasePlant
	{
		void onCreated(MyPlant plant)
		{
			plant.ShootOrProductCountdown = plant.ShootOrProductCountdown * 150 / 90;
			plant.ShootOrProductInterval = 90;
		}
	};
}
