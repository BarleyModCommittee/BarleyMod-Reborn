#include "pch.h"
#include "MyPlant/PlantAbility.hpp"
#include "MyZombie/ZombieAbility.hpp"
#include "MyEvents.hpp"

void onRandomZombieDropHelm(MyZombie zombie)
{
	if (zombie.Type != ZombieType::ConeheadZombie)
		return;

	zombie.BodyHealth = 6666666;
	zombie.Remove();
	int type = Creator::Rand(33);

	while (type == ZombieType::JackintheboxZombie
			|| type == ZombieType::BalloonZombie
			|| type == ZombieType::DiggerZombie
			|| type == ZombieType::BungeeZombie
			|| type == ZombieType::DrZomboss)
		type = Creator::Rand(33);

	MyBoard board = zombie.GetBoard();

	auto child_zombie = board.AddZombieInRow(static_cast<ZombieType::ZombieType>(type), zombie.Row, -1);
	//PVZ::CreateParticleSystem(zombie.X + 40.0f,zombie.Y + 65.0f,zombie.Layer+100,EffectType::IMITATER_TRANSFORMING);
	child_zombie.X = zombie.X;

	int health_ratio = 1 + Creator::Rand(10);
	child_zombie.BodyHealth = child_zombie.BodyHealth * health_ratio / 10;
	child_zombie.BodyMaxHealth = child_zombie.BodyMaxHealth * health_ratio / 10;
	child_zombie.HelmHealth = child_zombie.HelmHealth * health_ratio / 10;
	child_zombie.HelmMaxHealth = child_zombie.HelmMaxHealth * health_ratio / 10;
	child_zombie.ShieldHealth = child_zombie.ShieldHealth * health_ratio / 10;
	child_zombie.ShieldMaxHealth = child_zombie.ShieldMaxHealth * health_ratio / 10;

	return;
}

void InitZombieEvents()
{
	PVZEvent::ZombieDropHelmByDamageEvent((int)onRandomZombieDropHelm);
}