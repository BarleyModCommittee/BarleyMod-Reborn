namespace PVZ
{
	#pragma region DamageRangeFlags

	/// @brief 判定僵尸是否符合指定条件的标志位，以 DRF 开头。
	typedef unsigned char DamageRangeFlags;

	/// @brief 是否位于地面上（或水面上）。
	const DamageRangeFlags DRF_GROUND = (1 << 0);
	/// @brief 是否飞行。
	const DamageRangeFlags DRF_FLYING = (1 << 1);
	/// @brief 是否潜水。
	const DamageRangeFlags DRF_SUBMERGED = (1 << 2);
	/// @brief 内测版中用于判断是否为僵尸狗。正式版 PVZ 中被废弃。
	const DamageRangeFlags DRF_DOG = (1 << 3);
	/// @brief 是否正在落地（或出土）。
	const DamageRangeFlags DRF_OFF_GROUND = (1 << 4);
	/// @brief 是否考虑已被击杀的僵尸。
	const DamageRangeFlags DRF_DYING = (1 << 5);
	/// @brief 是否位于地下。
	const DamageRangeFlags DRF_UNDERGROUND = (1 << 6);
	/// @brief 是否被魅惑。
	const DamageRangeFlags DRF_HYPNOTIZED = (1 << 7);

	/// @brief 全体未被魅惑的僵尸。
	const DamageRangeFlags DRF_ALL = DRF_GROUND | DRF_FLYING
		| DRF_SUBMERGED | DRF_DOG | DRF_OFF_GROUND | DRF_DYING | DRF_UNDERGROUND;
	/// @brief 全体被魅惑的僵尸。
	const DamageRangeFlags DRF_ALL_HYPNOTIZED = DRF_HYPNOTIZED | DRF_ALL;

	#pragma endregion

	/// @brief 判定对僵尸伤害是否具有某种特效的标志位，以 DAMAGEF 开头。
	enum DamageFlags
	{
		/// @brief 无特效。
		DAMAGEF_NONE = 0,
		/// @brief 无视盾牌。
		DAMAGEF_BYPASSES_SHIELD = (1 << 0),
		/// @brief 穿透盾牌。
		DAMAGEF_HITS_SHIELD_AND_BODY = (1 << 1),
		/// @brief 有减速效果。
		DAMAGEF_FREEZE = (1 << 2),
		/// @brief 不导致僵尸闪烁。
		DAMAGEF_NOFLASH = (1 << 3),
		/// @brief 不显示击杀粒子效果。
		DAMAGEF_NOLEAVEBODY = (1 << 4),
		/// @brief 地刺类伤害，可以爆胎。
		DAMAGEF_SPIKE = (1 << 5),
	};
}