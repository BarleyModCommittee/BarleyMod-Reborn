#pragma once
#include "../PVZ.h"
#include "Board.hpp"

namespace PVZ
{
	/// @brief 部分类的基类
	/// @attention 你不应该直接构造这个类！
	class GameObject : public BaseClass
	{
	protected:
		GameObject() : BaseClass(0) {};
	public:
		/// @brief 获取 GameObject 所在的 PVZApp
		PVZApp GetLawnApp()
		{
			return(PVZ::PVZApp(Memory::ReadMemory<DWORD>(BaseAddress)));
		}
		/// @brief 获取当前对象所属的 Board
		/// @return 对象所在的 Board
		PVZ::Board GetBoard()
		{
			return(PVZ::Board(Memory::ReadMemory<int>(BaseAddress + 4)));
		}
		/// @brief X 坐标。部分派生类仅将其用作实际坐标的取整版本。
		INT_PROPERTY(ImageX, __get_ImageX, __set_ImageX, 8);
		/// @brief Y 坐标。部分派生类仅将其用作实际坐标的取整版本。
		INT_PROPERTY(ImageY, __get_ImageY, __set_ImageY, 0xC);
		/// @brief 宽度
		INT_PROPERTY(Width, __get_Width, __set_Width, 0x10);
		/// @brief 高度
		INT_PROPERTY(Height, __get_Height, __set_Height, 0x14);
		/// @brief 是否可见
		T_PROPERTY(BOOLEAN, Visible, __get_Visible, __set_Visible, 0x18);
		/// @brief 行
		INT_PROPERTY(Row, __get_Row, __set_Row, 0x1C);
		/// @brief 绘制图层编号
		INT_PROPERTY(Layer, __get_Layer, __set_Layer, 0x20);
	};
	/// @brief 僵尸
	class Zombie : public GameObject
	{
	public:
		Zombie(int indexoraddress);
		/// @brief 植物的内存占用字节数。\n
		///		若派生类需要对应扩指针的对象，请在派生类中修改此数值。
		static const DWORD MemSize = 0x15C;
		/// @brief 调整该类在 PVZ 中对象的大小。
		/// @note 请在派生类中调用这个函数。
		/// @note 调用该函数后，新生成的存档与原版存档不兼容，请注意清理。
		/// @param MemSize 更改后的大小。
		/// @param NewCount 调整后僵尸上限数
		static void SetMemSize(int NewSize, int NewCount);

		/// @deprecated
		struct AccessoriesType1
		{
			HelmType::HelmType Type;
			int Hp;
			int MaxHp;
		};
		/// @deprecated
		struct AccessoriesType2
		{
			ShieldType::ShieldType Type;
			int Hp;
			int MaxHp;
		};

		/// @brief 僵尸类型
		T_PROPERTY(ZombieType::ZombieType, Type, __get_Type, __set_Type, 0x24);
		/// @brief 僵尸状态
		T_PROPERTY(ZombieState::ZombieState, State, __get_State, __set_State, 0x28);
		/// @brief 实际 X 坐标
		T_PROPERTY(FLOAT, X, __get_X, __set_X, 0x2C);
		/// @brief 实际 Y 坐标
		T_PROPERTY(FLOAT, Y, __get_Y, __set_Y, 0x30);
		/// @brief 僵尸移动速度
		PROPERTY(FLOAT, __get_Speed, SetSpeed) Speed;
		/// @brief 是否显示舌头
		T_READONLY_PROPERTY(BOOLEAN, ShowingTongue, __get_ShowingTongue, 0x50);
		/// @brief 是否在吃东西
		T_READONLY_PROPERTY(BOOLEAN, Eating, __get_Eating, 0x51);
		void Light(int cs = 100);
		INT_PROPERTY(JustGotShotCounter, __get_JustGotShotCounter, __set_JustGotShotCounter, 0x54);
		INT_PROPERTY(ShieldJustGotShotCounter, __get_ShieldJustGotShotCounter, __set_ShieldJustGotShotCounter, 0x58);
		/// @brief 存在时间
		INT_READONLY_PROPERTY(ExistedTime, __get_ExistedTime, 0x60);
		INT_PROPERTY(ZombieHeight, __get_ZombieHeight, __set_ZombieHeight, 0x64);
		/// @brief 属性倒计时
		INT_PROPERTY(AttributeCountdown, __get_AttributeCountdown, __set_AttributeCountdown, 0x68);
		/// @brief 是否生成过掉落物
		T_PROPERTY(BOOLEAN, DroppedLoot, __get_DroppedLoot, __set_DroppedLoot, 0x70);
		/// @brief 消失倒计时
		INT_PROPERTY(DisappearCountdown, __get_DisappearCountdown, __set_DisappearCountdown, 0x74);
		/// @brief 蹦极僵尸目标列
		INT_PROPERTY(BungeeColumn, __get_BungeeColumn, __set_BungeeColumn, 0x80);
		/// @brief 高度
		T_PROPERTY(FLOAT, Height, __get_Height, __set_Height, 0x84);
		void GetCollision(CollisionBox* collbox);
		void SetCollision(CollisionBox* collbox);
		/// @brief 获取僵尸的基础攻击判定范围。
		/// @param collbox 攻击判定范围的存放位置。其中 X 和 Y 为相应坐标的偏移量。
		void GetAttackCollision(CollisionBox* collbox);
		/// @brief 设置僵尸的基础攻击判定范围。
		/// @param collbox 攻击判定范围的指针。其中 X 和 Y 为相应坐标的偏移量。
		void SetAttackCollision(CollisionBox* collbox);
		/// @brief 冰减速持续时间
		INT_PROPERTY(DecelerateCountdown, __get_DecelerateCountdown, __set_DecelerateCountdown, 0xAC);
		/// @brief 黄油定身持续时间
		INT_PROPERTY(FixedCountdown, __get_FixedCountdown, __set_FixedCountdown, 0xB0);
		/// @brief 冻结持续时间
		INT_PROPERTY(FrozenCountdown, __get_FrozenCountdown, __set_FrozenCountdown, 0xB4);
		/// @brief 是否被魅惑
		T_PROPERTY(BOOLEAN, Hypnotized, __get_Hypnotized, __set_Hypnotized, 0xB8);
		/// @brief 是否被吹飞
		T_PROPERTY(BOOLEAN, Blowaway, __get_Blowaway, __set_Blowaway, 0xB9);
		/// @brief 是否有头
		T_PROPERTY(BOOLEAN, NotDying, __get_NotDying, __set_NotDying, 0xBA);
		/// @brief 是否有手臂
		T_READONLY_PROPERTY(BOOLEAN, HandBroken, __get_HandBroken, 0xBB);
		/// @brief 是否有特殊物件
		T_PROPERTY(BOOLEAN, SthinHandOrYetiLeft, __get_SthinHandOrYetiLeft, __set_SthinHandOrYetiLeft, 0xBC);
		/// @brief 是否在水中
		T_PROPERTY(BOOLEAN, InWater, __get_InWater, __set_InWater, 0xBD);
		/// @brief 是否被大蒜影响
		T_PROPERTY(BOOLEAN, GarlicBited, __get_GarlicBited, __set_GarlicBited, 0xBF);
		/// @brief 头盔防具类型
		T_PROPERTY(HelmType::HelmType, HelmType, __get_HelmType, __set_HelmType, 0x0C4);
		/// @brief 本体生命值
		INT_PROPERTY(BodyHealth, __get_BodyHealth, __set_BodyHealth, 0x0C8);
		/// @brief 本体生命上限
		INT_PROPERTY(BodyMaxHealth, __get_BodyMaxHealth, __set_BodyMaxHealth, 0x0CC);
		/// @brief 头盔生命值
		INT_PROPERTY(HelmHealth, __get_HelmHealth, __set_HelmHealth, 0x0D0);
		/// @brief 头盔生命上限
		INT_PROPERTY(HelmMaxHealth, __get_HelmMaxHealth, __set_HelmMaxHealth, 0x0D4);
		/// @brief 盾牌防具类型
		T_PROPERTY(ShieldType::ShieldType, ShieldType, __get_ShieldType, __set_ShieldType, 0x0D8);
		/// @brief 盾牌生命值
		INT_PROPERTY(ShieldHealth, __get_ShieldHealth, __set_ShieldHealth, 0x0DC);
		/// @brief 盾牌生命上限
		INT_PROPERTY(ShieldMaxHealth, __get_ShieldMaxHealth, __set_ShieldMaxHealth, 0x0E0);
		/// @brief 气球生命值
		INT_PROPERTY(FlyingHealth, __get_FlyingHealth, __set_FlyingHealth, 0x0E4);
		/// @brief 气球生命上限
		INT_PROPERTY(FlyingMaxHealth, __get_FlyingMaxHealth, __set_FlyingMaxHealth, 0xE8);
		/// @brief 是否已移除
		T_PROPERTY(BOOLEAN, NotExist, __get_NotExist, __set_NotExist, 0xEC);
		/// @brief 关联僵尸的识别 ID
		INT_PROPERTY(RelatedZombieID, __get_RelatedZombieID, __set_RelatedZombieID, 0x0F0);
		/// @brief 获取僵尸动画
		/// @return 僵尸动画
		PVZ::Animation GetAnimation();
		/// @brief 僵王召唤僵尸的倒计时。同时也是投手僵尸剩余篮球数。
		INT_PROPERTY(SummonCounter, __get_SummonCounter, __set_SummonCounter, 0x114);
		/// @brief 大小
		T_PROPERTY(FLOAT, Size, __get_Size, __set_Size, 0x11C);
		//临时变量
		INT_PROPERTY(Temp, __get_Temp, __set_Temp, 0x12C);
		/// @brief 获取特殊头部动画（如植物僵尸的植物头）
		/// @return 特殊头部动画
		Animation GetSpecialHeadAnimation();
		/// @brief 设置特殊头部动画（如植物僵尸的植物头）
		/// @param anim 特殊头部动画
		void SetSpecialHeadAnimation(Animation anim);
		/// @brief 识别 ID
		INT_READONLY_PROPERTY(Id, __get_Id, 0x158);
		READONLY_PROPERTY_BINDING(int, __get_Index, Id & 0xFFFF) Index;
		/// @brief 对僵尸造成伤害
		/// @param damage 伤害
		/// @param flags 伤害标签
		void Hit(int damage, DamageFlags flags = DAMAGEF_NONE);
		/// @brief 忽略所有护甲，对僵尸本体造成伤害
		/// @param damage 伤害
		/// @param flags 伤害标签
		void HitBody(int damage, DamageFlags flags = DAMAGEF_NONE);
		/// @brief 令僵尸化灰，对本体生命值大于 1800 的僵尸造成 1800 点伤害。
		void Blast();
		/// @brief 对僵尸施加黄油效果
		/// @param countdown 持续时间
		void Butter(int countdown);
		/// @brief 减速僵尸，无法减速默认免疫减速的僵尸。
		/// @param countdown 持续时间
		void Decelerate(int countdown);
		/// @brief 冻结僵尸，无法冻结默认免疫冻结的僵尸。
		/// @note 不造成冻结伤害。\n
		///		不影响减速时长。
		/// @param countdown 持续时间
		void Froze(int countdown);
		/// @brief 魅惑此僵尸
		void Hypnotize();
		/// @brief 移除僵尸
		void Remove();
		/// @brief 移除僵尸并生成它的掉落物。
		void RemoveWithLoot();
		//LoopType(APA_XXXXXX)
		void SetAnimation(LPCSTR animName, PVZEnum::ReanimLoopType LoopType, int blend_time = 14, float fps = 24.0f);
		/// @brief 为僵尸装备铁桶
		/// @param shield 铁桶生命值
		void EquipBucket(int shield = 1100);
		/// @brief 为僵尸装备路障
		/// @param shield 路障生命值
		void EquipCone(int shield = 370);
		/// @brief 设置僵尸动画轨道在绘制时的渲染分组。
		/// @param trackPrefix 受影响轨道的名称的前缀。
		/// @param renderGroup 调整后轨道组号。组号越大则图层越上层，为 -1 时隐藏。
		void ReanimShowPrefix(const char* trackPrefix, int renderGroup);
		/// @brief 僵尸是否可被冰减速
		/// @return 是否可被冰减速
		bool canDecelerate();
		/// @brief 僵尸是否可被冻结
		/// @todo 将该函数改为完全调用内置函数的版本。
		/// @return 是否可被冻结
		bool canFroze();
		/// @brief 判定僵尸是否能被指定索敌类型搜寻到。
		/// @param range 索敌类型。
		/// @param usepvzfunc 是否调用 pvz 内部函数。默认为 true。
		/// @return 是否能被搜寻到。
		bool EffectedBy(DamageRangeFlags range, bool usepvzfunc = true);
		/// @brief 僵尸运动或状态改变时调用，更新动画速度。
		void UpdateAnimSpeed();
		/// @brief 随机刷新僵尸的移动速度。
		void PickRandomSpeed();

		/// @brief 获取僵尸的实际可攻击范围。
		/// @return 僵尸的实际攻击范围
		Rect GetActualAttackRect();
		/// @brief 获取僵尸的实际受击范围。
		/// @return 僵尸的实际受击范围
		Rect GetActualRect();

		/// @brief 设置是否显示铁门僵尸的手臂。
		/// @param shown 是否显示，默认为 true
		void ShowDoorArms(bool shown = true);
		/// @brief 根据盾的类型设置相应动画轨道的绘制分组。
		void AttachShield();

		/// @deprecated
		void GetBodyHp(int* hp, int* maxhp);
		/// @deprecated
		void SetBodyHp(int hp, int maxhp);
		/// @deprecated
		AccessoriesType1 GetAccessoriesType1();
		/// @deprecated
		void SetAccessoriesType1(AccessoriesType1 acctype1);
		/// @deprecated
		AccessoriesType2 GetAccessoriesType2();
		/// @deprecated
		void SetAccessoriesType2(AccessoriesType2 acctype2);
	};
	/// @brief 植物
	class Plant : public GameObject
	{
	public:
		/// @brief 植物的内存占用字节数。\n
		///		若派生类需要对应扩指针的对象，请在派生类中修改此数值。
		static const int MemSize = 0x14C;
		Plant(int indexoraddress);
		/// @brief 调整该类在 PVZ 中对象的大小。
		/// @note 请在派生类中调用这个函数。
		/// @note 调用该函数后，新生成的存档与原版存档不兼容，请注意清理。
		/// @param MemSize 更改后的大小。
		/// @param NewCount 调整后植物上限数
		static void SetMemSize(int NewSize, int NewCount);
		/// @brief 类型
		T_PROPERTY(SeedType::SeedType, Type, __get_Type, __set_Type, 0x24);
		/// @brief 列
		INT_PROPERTY(Column, __get_Column, __set_Column, 0x28);
		/// @brief 植物状态
		/// @see PlantState
		T_PROPERTY(PlantState::PlantState, State, __get_State, __set_State, 0x3C);
		/// @brief 当前生命值
		INT_PROPERTY(Hp, __get_Hp, __set_Hp, 0x40);
		/// @brief 最大生命值
		INT_PROPERTY(MaxHp, __get_MaxHp, __set_MaxHp, 0x44);
		/// @brief 植物子类别
		INT_PROPERTY(SubClass, __get_SubClass, __set_SubClass, 0x48);
		/// @deprecated
		T_PROPERTY(BOOLEAN, Aggressive, __get_Aggressive, __set_Aggressive, 0x48);
		/// @brief 消失倒计时
		INT_PROPERTY(BloverDisappearCountdown, __get_BloverDisappearCountdown, __set_BloverDisappearCountdown, 0x4C);
		/// @brief 一次性植物发动技能的倒计时
		INT_PROPERTY(EffectiveCountdown, __get_EffectiveCountdown, __set_EffectiveCountdown, 0x50);
		/// @brief 各种倒计时
		INT_PROPERTY(AttributeCountdown, __get_AttributeCountdown, __set_AttributeCountdown, 0x54);
		/// @brief 植物射击（或产出物品）的倒计时
		INT_PROPERTY(ShootOrProductCountdown, __get_ShootOrProductCountdown, __set_ShootOrProductCountdown, 0x58);
		/// @brief 植物射击（或产出物品）的基础间隔
		INT_PROPERTY(ShootOrProductInterval, __get_ShootOrProductInterval, __set_ShootOrProductInterval, 0x5C);
		/// @brief 目标 X 坐标
		INT_PROPERTY(mTargetX, __get_mTargetX, __set_mTargetX, 0x80);
		/// @brief 目标 Y 坐标
		INT_PROPERTY(mTargetY, __get_mTargetY, __set_mTargetY, 0x84);
		/// @brief 粒子效果识别 ID
		T_PROPERTY(DWORD, ParticleID, __get_ParticleID, __set_ParticleID, 0x8C);
		/// @brief 射击动作倒计时
		INT_PROPERTY(ShootingCountdown, __get_ShootingCountdown, __set_ShootingCountdown, 0x90);
		/// @brief 获取植物的第一个动画
		/// @return 第一个动画
		PVZ::Animation GetAnimationPart1();
		PVZ::Animation GetAnimationPart2();
		PVZ::Animation GetAnimationPart3();
		PVZ::Animation GetAnimationPart4();
		/// @brief 获取植物的眨眼动画
		/// @return 植物的眨眼动画
		PVZ::Animation GetAnimationEyeBlink();
		PVZ::Animation GetAnimationPotatoGlow();
		/// @brief 获取植物的睡眠动画
		/// @return 植物的睡眠动画
		PVZ::Animation GetAnimationSleep();
		void Light(int cs = 100);
		void Flash(int cs = 100);
		T_PROPERTY(FLOAT, ImageXOffset, __get_ImageXOffset, __set_ImageXOffset, 0xC0);
		T_PROPERTY(FLOAT, ImageYOffset, __get_ImageYOffset, __set_ImageYOffset, 0xC4);
		/// @brief 目标僵尸的识别 ID
		T_PROPERTY(DWORD, mTargetZombieID, __get_mTargetZombieID, __set_mTargetZombieID, 0x12C);
		/// @brief 苏醒倒计时
		INT_PROPERTY(mWakeUpCounter, __get_mWakeUpCounter, __set_mWakeUpCounter, 0x130);
		/// @brief 被蹦极抱起的状态
		INT_PROPERTY(mOnBungee, __get_mOnBungee, __set_mOnBungee, 0x134);
		/// @brief 是否已消失
		T_PROPERTY(BOOLEAN, NotExist, __get_NotExist, __set_NotExist, 0x141);
		/// @brief 是否已被压扁
		T_PROPERTY(BOOLEAN, Squash, __get_Squash, __set_Squash, 0x142);
		/// @brief 是否已睡着
		T_READONLY_PROPERTY(BOOLEAN, Sleeping, __get_Sleeping, 0x143);
		/// @brief 设置植物是否睡着
		/// @param sleeping 植物是否睡着
		void SetSleeping(bool sleeping);
		/// @brief 识别 ID
		INT_READONLY_PROPERTY(Id, __get_Id, 0x148);
		READONLY_PROPERTY_BINDING(int, __get_Index, Id & 0xFFFF) Index;
		void CreateEffect();
		/// @brief 将植物定身为纸板（同 IZ）。
		/// @note 会让土豆地雷直接出土。
		void SetStatic();
		/// @brief 压扁该植物
		void Smash();
		/// @brief 根据植物的当前位置，计算植物应当处于的图层编号
		/// @return 植物应当所在的图层编号
		int CalcLayer();
		/// @brief 移动至指定位置，并更新相关属性
		/// @param row 行
		/// @param column 列
		void MoveTo(int row, int column);
		/// @brief 移除该植物
		void Remove();
		/// @deprecated
		PVZ::Projectile Shoot(int targetid = -1);
		/// @brief 立刻发射子弹
		/// @param motiontype 子弹移动类型
		/// @param targetid 攻击目标僵尸的 ID
		/// @param special 是否使用副武器进行攻击
		/// @return 生成的子弹
		PVZ::Projectile Shoot(MotionType::MotionType motiontype = MotionType::None, int targetid = -1, bool special = false);
		//animPlayArg(APA_XXXXXX)
		void SetAnimation(LPCSTR animName, PVZEnum::ReanimLoopType animPlayArg, int imagespeed);
		/// @brief 以指定帧频播放闲置动画。IZ 关卡中动画速率会设为 0 。
		/// @param speed 指定的帧频
		void PlayIdleAnim(float speed);
		class MagnetItem
		{
			int BaseAddress;
		public:
			MagnetItem(int address);
			T_PROPERTY(FLOAT, X, __get_X, __set_X, 0);
			T_PROPERTY(FLOAT, Y, __get_Y, __set_Y, 4);
			T_PROPERTY(FLOAT, DestOffsetX, __get_DestOffsetX, __set_DestOffsetX, 8);
			T_PROPERTY(FLOAT, DestOffsetY, __get_DestOffsetY, __set_DestOffsetY, 0xC);
			T_PROPERTY(MagnetItemType::MagnetItemType, Type, __get_Type, __set_Type, 0x10);
		};
		MagnetItem GetMagnetItem(int num);

		/// @brief 取得植物种植时的基础阳光消耗。
		/// @note 对其他类型的卡牌也有效
		/// @param type 种子卡类型
		/// @param imitater_type 模仿者模仿的类型
		/// @return 种植的基础阳光消耗
		static int GetCost(SeedType::SeedType type, SeedType::SeedType imitater_type = SeedType::None);
	};
	/// @brief 各种掉落物
	class Coin : public GameObject
	{
	public:
		/// @brief 掉落物的内存占用字节数。\n
		///		若派生类需要对应扩指针的对象，请在派生类中修改此数值。
		static const DWORD MemSize = 0x0D8;
		Coin(int indexoraddress);
		INT_READONLY_PROPERTY(ImageXVariation, __get_ImageXVariation, 8);
		INT_READONLY_PROPERTY(ImageYVariation, __get_ImageYVariation, 0xC);
		void GetCollision(Rect* collbox);
		void SetCollision(Rect* collbox);
		/// @brief 实际 X 坐标
		T_PROPERTY(FLOAT, X, __get_X, __set_X, 0x24);
		/// @brief 实际 Y 坐标
		T_PROPERTY(FLOAT, Y, __get_Y, __set_Y, 0x28);
		/// @brief 大小
		T_PROPERTY(FLOAT, Size, __get_Size, __set_Size, 0x34);
		/// @brief 是否已消失
		T_PROPERTY(BOOLEAN, NotExist, __get_NotExist, __set_NotExist, 0x38);
		/// @brief 已存在时间
		INT_READONLY_PROPERTY(ExistedTime, __get_ExistedTime, 0x4C);
		/// @brief 是否已被收集
		T_PROPERTY(BOOLEAN, Collected, __get_Collected, __set_Collected, 0x50);
		/// @brief 消失倒计时
		INT_PROPERTY(DisappearCounter, __get_DisappearCounter, __set_DisappearCounter, 0x54);
		/// @brief 物品类型
		T_PROPERTY(CoinType::CoinType, Type, __get_Type, __set_Type, 0x58);
		/// @brief 该物品的移动类型
		T_PROPERTY(CoinMotionType::CoinMotionType, Motion, __get_Motion, __set_Motion, 0x5C);
		/// @brief 获取该物品的附件
		/// @return 该物品的附件
		PVZ::Attachment GetAttachment();
		/// @brief 种子卡片的种子类型
		T_PROPERTY(SeedType::SeedType, ContentCard, __get_ContentCard, __set_ContentCard, 0x68);
		/// @brief 获取该掉落物对应的花园盆栽
		/// @return 该掉落物对应的花园盆栽
		PVZ::GardenPlant GetGardenPlant();
		/// @brief 是否有光环视觉效果
		T_PROPERTY(BOOLEAN, HasHalo, __get_HasHalo, __set_HasHalo, 0xC8);
		/// @brief 识别 ID.
		INT_READONLY_PROPERTY(Id, __get_Id, 0xD4);
		READONLY_PROPERTY_BINDING(int, __get_Index, Id & 0xFFFF) Index;
		void Collect();
		void Die();
	};
	/// @brief 子弹
	class Projectile : public GameObject
	{
	public:
		/// @brief 子弹的内存占用字节数。\n
		///		若派生类需要对应扩指针的对象，请在派生类中修改此数值。
		static const DWORD MemSize = 0x94;
		Projectile(int indexoraddress);
		/// @brief 实际 X 坐标
		T_PROPERTY(FLOAT, X, __get_X, __set_X, 0x30);
		/// @brief 子弹本体的 Y 坐标
		T_PROPERTY(FLOAT, Y, __get_Y, __set_Y, 0x34);
		/// @brief 子弹 Z 坐标
		T_PROPERTY(FLOAT, Height, __get_Height, __set_Height, 0x38);
		/// @brief X 方向坐标
		T_PROPERTY(FLOAT, XSpeed, __get_XSpeed, __set_XSpeed, 0x3C);
		T_PROPERTY(FLOAT, YSpeed, __get_YSpeed, __set_YSpeed, 0x40);
		T_PROPERTY(FLOAT, HeightSpeed, __get_HeightSpeed, __set_HeightSpeed, 0x44);
		T_PROPERTY(FLOAT, HeightAcceleration, __get_HeightAcceleration, __set_HeightAcceleration, 0x48);
		/// @brief 影子 Y 坐标
		T_PROPERTY(FLOAT, ShadowY, __get_ShadowY, __ShadowY, 0x4C);
		/// @brief 是否已移除
		T_PROPERTY(BOOLEAN, NotExist, __get_NotExist, __set_NotExist, 0x50);
		/// @brief 子弹运动类型
		T_PROPERTY(MotionType::MotionType, Motion, __get_Motion, __set_Motion, 0x58);
		/// @brief 子弹类型
		T_PROPERTY(ProjectileType::ProjectileType, Type, __get_Type, __set_Type, 0x5C);
		/// @brief 存在时间
		INT_READONLY_PROPERTY(ExistedTime, __get_ExistedTime, 0x60);
		/// @brief 旋转大小，暂不确定单位是否为弧度。
		T_PROPERTY(FLOAT, RotationAngle, __get_RotationAngle, __set_RotationAngle, 0x68);
		/// @brief 旋转速度，尚不确认是否是角速度。
		T_PROPERTY(FLOAT, RotationSpeed, __get_RotationSpeed, __set_RotationSpeed, 0x6C);
		/// @brief 子弹索敌标签
		T_PROPERTY(DamageRangeFlags, DamageAbility, __get_DamageAbility, __set_DamageAbility, 0x74);
		/// @brief 对于跟踪弹道，表示跟踪目标僵尸的 ID 。
		INT_PROPERTY(TracktargetId, __get_TracktargetId, __set_TracktargetId, 0x88);
		/// @brief 识别 ID
		INT_READONLY_PROPERTY(Id, __get_Id, 0x90);
		READONLY_PROPERTY_BINDING(int, __get_Index, Id & 0xFFFF) Index;
		/// @brief 子弹过火，转化为火球
		void OnFire();
		/// @brief 移除该子弹。
		void Remove();
	};
}