#include "MyPlant.hpp"
#include "implement/Index.hpp"

namespace PlantAbility
{
	PlantAbility::PlantPTR pt_factory[] =
	{
		new PeaPlant(), new BasePlant(), new BasePlant(), new BasePlant(),
		new BasePlant(), new PeaPlant(), new BasePlant(), new PeaPlant(),

		new PuffShroom(), new BasePlant(), new FumeShroom(), new BasePlant(),
		new BasePlant(), new ScaredyShroom(), new BasePlant(), new BasePlant(),

		new BasePlant(), new BasePlant(), new PeaPlant(), new BasePlant(),
		new BasePlant(), new BasePlant(), new BasePlant(), new BasePlant(),

		new SeaShroom(), new BasePlant(), new Cactus(), new BasePlant(),
		new PeaPlant(), new BasePlant(), new BasePlant(), new BasePlant(),

		new PultPlant(), new BasePlant(), new PultPlant(), new BasePlant(),
		new BasePlant(), new BasePlant(), new BasePlant(), new PultPlant(),

		new PeaPlant(), new BasePlant(), new BasePlant(), new Cattail(),
		new PultPlant(), new BasePlant(), new BasePlant(), new BasePlant(),

		new BasePlant(), new BasePlant(), new BasePlant(), new BasePlant(),
		new BasePlant(), new BasePlant(), new BasePlant(), new BasePlant(),
	};
}

PlantAbility::PlantPTR PlantAbility::GetAbility(SeedType::SeedType type)
{
	return PlantAbility::pt_factory[type];
}