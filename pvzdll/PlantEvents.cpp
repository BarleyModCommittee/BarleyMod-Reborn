#include "pch.h"
#include "MyPlant/PlantAbility.hpp"

void onPlantInitAfter(MyPlant plant)
{
	PlantAbility::GetAbility(plant.Type)->onCreated(plant);
}

static void onChomperChewStart(MyPlant plant)
{
	plant.AttributeCountdown = 2000;
}

void InitPlantEvents()
{
	PlantInitAfterEvent((int)onPlantInitAfter);
	PVZEvent::ChomperChewStartEvent((int)onChomperChewStart);
}