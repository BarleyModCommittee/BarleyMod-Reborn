#pragma once
#include "../PlantAbility.hpp"

namespace PlantAbility
{
	class FumeShroom : public BasePlant
	{
		void onCreated(MyPlant plant)
		{
			plant.ShootOrProductCountdown = plant.ShootOrProductCountdown * 150 / 80;
			plant.ShootOrProductInterval = 80;
		}
	};
}
