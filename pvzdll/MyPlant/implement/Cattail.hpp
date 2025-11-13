#pragma once
#include "../PlantAbility.hpp"

namespace PlantAbility
{
	class Cattail : public BasePlant
	{
		void onCreated(MyPlant plant)
		{
			plant.ShootOrProductCountdown = plant.ShootOrProductCountdown * 150 / 120;
			plant.ShootOrProductInterval = 120;
		}
	};
}
