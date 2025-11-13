#pragma once
namespace MouseType
{

	enum MouseType
	{
		None,
		SlotPlant,
		CoinPlant,
		GlovePlant,
		DuplicatorPlant,
		WheelBarrowPlant,
		Shovel,
		Hammer,
		Crosshair,
		Watering,
		Fertilizer,
		BugSpray,
		Phonograph,
		Chocolate,
		GardeningGlove,
		Sell,
		WheelBarrow,
		TreeFood,
	};
	constexpr MouseType CobCannonTarget = Crosshair;

	extern const char* ToString(MouseType mouset);

}