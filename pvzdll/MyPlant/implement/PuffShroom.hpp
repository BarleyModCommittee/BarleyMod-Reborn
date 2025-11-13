#pragma once
#include "../PlantAbility.hpp"

namespace PlantAbility
{
	class PuffShroom : public BasePlant
	{
		void onCreated(MyPlant plant)
		{
			plant.ShootOrProductCountdown = plant.ShootOrProductCountdown * 150 / 60;
			plant.ShootOrProductInterval = 60;
		}
	};
}
