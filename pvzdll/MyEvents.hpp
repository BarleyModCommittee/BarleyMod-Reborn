#pragma once
#include "../pvzclass/Events/DLLEvent.h"

namespace PVZEvent
{
	/// @brief 大嘴花吞噬僵尸事件。\n
	///		取消该事件将不会结算啃咬伤害。若希望结算伤害，请使用其他事件。
	/// @param 依次为：触发事件的植物、该植物啃食的僵尸。
	/// @return 是否吞噬此僵尸。
	class ChomperDevourEvent : public BoolDLLEventTemplate<0x4614F9, 5, 0x4614E5, REG_ESI, REG_EDI>
	{
	public:
		ChomperDevourEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		ChomperDevourEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		ChomperDevourEvent() : ChomperDevourEvent("onChomperDevour") {};
	};

	/// @brief 大嘴花开始咀嚼事件。\n
	///		时机上落后于原版的设置。
	/// @param 触发事件的植物
	class ChomperChewStartEvent : public DLLEventTemplate<0x461555, 5, REG_EDI>
	{
	public:
		ChomperChewStartEvent(const char* str) : DLLEventTemplate() { Init(str); };
		ChomperChewStartEvent(int address) : DLLEventTemplate() { Init(address); };
		ChomperChewStartEvent() : ChomperChewStartEvent("onChomperChewStart") {};
	};

	/// @brief 大嘴花完成咀嚼事件。\n
	///		时机上落后于原版的设置。
	/// @note 大嘴花吞噬失败也会触发这个事件。
	/// @param 触发事件的植物
	class ChomperChewFinishEvent : public DLLEventTemplate<0x4615BF, 7, REG_EDI>
	{
	public:
		ChomperChewFinishEvent(const char* str) : DLLEventTemplate() { Init(str); };
		ChomperChewFinishEvent(int address) : DLLEventTemplate() { Init(address); };
		ChomperChewFinishEvent() : ChomperChewFinishEvent("onChomperChewFinish") {};
	};

	/// @brief 植物更新特殊外观事件
	/// @param 触发事件的植物
	/// @return 是否结算原版对部分植物的特殊外观设定。
	class PlantSpecialAnimateEvent : public BoolDLLEventTemplate<0x464E4E, 6, 0x464E7C, REG_EDI>
	{
	public:
		PlantSpecialAnimateEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		PlantSpecialAnimateEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		PlantSpecialAnimateEvent() : PlantSpecialAnimateEvent("onPlantSpecialAnimate") {};
	};

	/// @brief 获取子弹伤害标签事件
	/// @param 触发事件的子弹，子弹击中的僵尸
	/// @return 伤害标签，负值会被忽略。
	class ProjectileDmgFlagEvent : public IntDLLEventTemplate<0x46D230, 6, 0, 0, 0, REG_EAX, true, REG_EAX, REG_EDI>
	{
	public:
		ProjectileDmgFlagEvent(const char* str) : IntDLLEventTemplate() { Init(str); };
		ProjectileDmgFlagEvent(int address) : IntDLLEventTemplate() { Init(address); };
		ProjectileDmgFlagEvent() : ProjectileDmgFlagEvent("GetProjectileDmgFlag") {};
	};

	/// @brief 植物获取伤害范围标签事件
	/// @param 植物、PlantWeapon
	/// @return 伤害标签，负值会回到原版更新，非零值会跳过原版直接返回
	class PlantGetDamageRangeFlagsEvent : public DLLEventTemplate<0x45EB10, 6, MEM_ESP_ADD(0x4), REG_EAX>
	{
	public:
		PlantGetDamageRangeFlagsEvent(const char* str) : DLLEventTemplate() { Init(str); };
		PlantGetDamageRangeFlagsEvent(int address) : DLLEventTemplate() { Init(address); };
		PlantGetDamageRangeFlagsEvent() : PlantGetDamageRangeFlagsEvent("onPlantGetDamageRangeFlags") {};
	protected:
		virtual void InitExtra(AsmBuilder& builder)
		{
			builder.cmp_reg_imm(REG_EAX, 0).jl_rel(8);
			builder.mov_mem_esp_add_imm8_reg(0x1C - ((REG_EAX & 7) << 2), REG_EAX).popad();
			builder.retn(0x4);
		}
	};

	/// @brief 辣椒僵尸爆炸事件
	/// @param 触发事件的僵尸
	/// @return 是否执行烧毁植物的部分。
	class JalapenoZombieBurnEvent : public BoolDLLEventTemplate<0x5276BB, 7, 0x52773E, REG_EDI>
	{
	public:
		JalapenoZombieBurnEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		JalapenoZombieBurnEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		JalapenoZombieBurnEvent() : JalapenoZombieBurnEvent("onJalapenoZombieBurn") {};
	};

	/// @brief 冰车僵尸更新冰道事件
	/// @param 触发事件的僵尸
	/// @return 是否更新冰道。
	class ZomboniUpdateIceEvent : public BoolDLLEventTemplate<0x52A865, 6, 0x52A8D6, REG_ESI>
	{
	public:
		ZomboniUpdateIceEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		ZomboniUpdateIceEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		ZomboniUpdateIceEvent() : ZomboniUpdateIceEvent("onZomboniUpdateIce") {};
	};

	/// @brief 僵尸发射子弹事件（复合事件）
	/// @param 触发事件的僵尸，僵尸发射的子弹
	class ZombieAddProjectileEvent
	{
	private:
		class Gatling : public DLLEventTemplate<0x527A98, 7, REG_ESI, MEM_ESP_ADD(0x28)>
		{
		public:
			Gatling(const char* str) : DLLEventTemplate() { Init(str); };
			Gatling(int address) : DLLEventTemplate() { Init(address); };
		};
		class PeaHead : public DLLEventTemplate<0x5275B6, 6, REG_EAX, REG_EDI>
		{
		public:
			PeaHead(const char* str) : DLLEventTemplate() { Init(str); };
			PeaHead(int address) : DLLEventTemplate() { Init(address); };
		};
		class Catapult1 : public DLLEvent
		{
		public:
			Catapult1()
			{
				hookAddress = 0x5257D9;
				rawlen = 6;
				PVZ::Memory::AllAccess(0x525884);
				BYTE code[] = { MOV_PTR_ADDR_EUX(REG_ESI, 0x525884)};
				start(STRING(code));
			};
		};
		class Catapult2 : public DLLEvent
		{
		public:
			Catapult2(int address)
			{
				hookAddress = 0x52587B;
				rawlen = 6;
				BYTE code[] =
				{
					PUSH_ESI,
					PUSH_PTR(0x525884),
					INVOKE(address),
					ADD_ESP(8)
				};
				start(STRING(code));
			};
			Catapult2(const char* str) : Catapult2(PVZ::Memory::GetProcAddress(str)) { };
		};
		Gatling* gatling;
		PeaHead* pea;
		Catapult1* catapult1;
		Catapult2* catapult2;
	public:
		ZombieAddProjectileEvent(int address)
		{
			gatling = new Gatling(address);
			pea = new PeaHead(address);
			catapult1 = new Catapult1();
			catapult2 = new Catapult2(address);
		}
		ZombieAddProjectileEvent(const char* str) : ZombieAddProjectileEvent(PVZ::Memory::GetProcAddress(str)) {};
		ZombieAddProjectileEvent() : ZombieAddProjectileEvent("onZombieAddProjectile") {};
		void end()
		{
			gatling->end();
			pea->end();
			catapult1->end();
			catapult2->end();
		}
	};

	/// @brief 子弹击中僵尸事件
	/// @param 依次为：触发事件的子弹，子弹击中的僵尸
	class ProjectileImpactEvent : public DLLEventTemplate<0x46E000, 5, REG_EAX, REG_ECX>
	{
	public:
		ProjectileImpactEvent(const char* str) : DLLEventTemplate() { Init(str); };
		ProjectileImpactEvent(int address) : DLLEventTemplate() { Init(address); };
		ProjectileImpactEvent() : ProjectileImpactEvent("onProjectileImpact") {};
	};

	/// @brief 子弹总更新事件，发生在计时器与图层更新后、子弹运动前
	/// @param 子弹ID
	class ProjectileUpdateEvent : public DLLEventTemplate<0x46E4FE, 6, REG_ESI>
	{
	public:
		ProjectileUpdateEvent(const char* str) : DLLEventTemplate() { Init(str); };
		ProjectileUpdateEvent(int address) : DLLEventTemplate() { Init(address); };
		ProjectileUpdateEvent() : ProjectileUpdateEvent("onProjectileUpdate") {};
	};

	/// @brief 三线边路运动方式的子弹的更新事件
	/// @param 子弹ID
	/// @return False则跳过原版运动方式更新
	class ProjectileSlideMotionEvent : public BoolDLLEventTemplate<0x46DBF6, 6, 0x46DC1F, REG_EBX>
	{
	public:
		ProjectileSlideMotionEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		ProjectileSlideMotionEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		ProjectileSlideMotionEvent() : ProjectileSlideMotionEvent("onProjectileSlideMotion") {};
	};

	/// @brief 大嘴花判定是否秒杀僵尸的事件
	/// @param 依次为：触发事件的植物，植物攻击的僵尸
	class ChomperInstantJudgeEvent : public IntDLLEventTemplate<0x461444, 6, 0, 0, 0, REG_EDX, false, REG_ESI, REG_EDI>
	{
	public:
		ChomperInstantJudgeEvent(const char* str) : IntDLLEventTemplate() { Init(str); };
		ChomperInstantJudgeEvent(int address) : IntDLLEventTemplate() { Init(address); };
		ChomperInstantJudgeEvent() : ChomperInstantJudgeEvent("onChomperInstantJudge") {};
	};

	/// @brief 大嘴花判定是否秒杀僵尸的事件
	/// @param 依次为：触发事件的植物，植物攻击的僵尸
	class ZombieCanBeChilledEvent : public IntDLLEventTemplate<0x531990, 6, 0, 0, 0, REG_EDX, true, REG_ESI>
	{
	public:
		ZombieCanBeChilledEvent(const char* str) : IntDLLEventTemplate() { Init(str); };
		ZombieCanBeChilledEvent(int address) : IntDLLEventTemplate() { Init(address); };
		ZombieCanBeChilledEvent() : ZombieCanBeChilledEvent("IsZombieCanBeChilled") {};
	};

	class ZombieDropHelmByDamageEvent : public DLLEventTemplate<0x531070, 5, REG_EBP>
	{
	public:
		ZombieDropHelmByDamageEvent(const char* str) : DLLEventTemplate() { Init(str); };
		ZombieDropHelmByDamageEvent(int address) : DLLEventTemplate() { Init(address); };
		ZombieDropHelmByDamageEvent() : ZombieDropHelmByDamageEvent("onZombieDropHelmByDamage") {};
	};

	/// @brief 物品自动收集事件，注入功能：存在1秒后自动设置自己为被收集状态
	/// @param 物品的ID
	class CoinAutoCollectEvent : public DLLEventTemplate<0x43158B, 6, REG_EBX>
	{
	public:
		CoinAutoCollectEvent(const char* str) : DLLEventTemplate() { Init(str); };
		CoinAutoCollectEvent(int address) : DLLEventTemplate() { Init(address); };
		CoinAutoCollectEvent() : CoinAutoCollectEvent("onCoinAutoCollect") {};
	protected:
		virtual void InitExtra(AsmBuilder& builder)
		{
			builder.test_al_al().jz_rel(7).popad().push_imm32(0x431599).ret().popad().push_imm32(0x431591).ret();
		}
	};

	/// @brief 辣椒烧僵尸事件
	/// @param 触发事件的植物，植物烧的僵尸
	class JalapenoBurnEvent : public DLLEventTemplate<0x466528, 5, REG_ESI, REG_EDI>
	{
	public:
		JalapenoBurnEvent(const char* str) : DLLEventTemplate() { Init(str); };
		JalapenoBurnEvent(int address) : DLLEventTemplate() { Init(address); };
		JalapenoBurnEvent() : JalapenoBurnEvent("onJalapenoBurn") {};
	};

	/// @brief 小推车割僵尸事件
	/// @param 触发事件的小推车，小推车割的僵尸
	class LawnmowerMowZombieEvent : public DLLEventTemplate<0x458540, 6, MEM_ESP_ADD(0x20), REG_EAX>
	{
	public:
		LawnmowerMowZombieEvent(const char* str) : DLLEventTemplate() { Init(str); };
		LawnmowerMowZombieEvent(int address) : DLLEventTemplate() { Init(address); };
		LawnmowerMowZombieEvent() : LawnmowerMowZombieEvent("onLawnmowerMowZombie") {};
	};

	/// @brief 植物开始眨眼事件
	/// @param 触发事件的植物
	/// @return 是否眨眼
	class PlantStartBlinkEvent : public BoolDLLEventTemplate<0x464341, 5, 0x464383, REG_ESI>
	{
	public:
		PlantStartBlinkEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		PlantStartBlinkEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		PlantStartBlinkEvent() : PlantStartBlinkEvent("onPlantStartBlink") {};
	};

	/// @brief 植物开始攻击动作事件
	/// @param 触发事件的植物，植物选择的目标僵尸，植物是否使用副武器
	class NormalPlantAttackStartEvent : public DLLEventTemplate<0x45EF3F, 6, MEM_ESP_ADD(0x3C), MEM_ESP_ADD(0x34), REG_ESI>
	{
	public:
		NormalPlantAttackStartEvent(const char* str) : DLLEventTemplate() { Init(str); };
		NormalPlantAttackStartEvent(int address) : DLLEventTemplate() { Init(address); };
		NormalPlantAttackStartEvent() : NormalPlantAttackStartEvent("onNormalPlantAttackStart") {};
	};

	/// @brief 修改植物的颜色
	/// @param 植物（ESI）、动画ID（EBX）
	/// @return True则无颜色修改，与原版相同
	class PlantUpdateColorEvent : public BoolDLLEventTemplate<0x463714, 6, 0x463720, REG_EBX, REG_ESI>
	{
	public:
		PlantUpdateColorEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		PlantUpdateColorEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		PlantUpdateColorEvent() : PlantUpdateColorEvent("onPlantUpdateColor") {};
	};

	/// @brief 攻击型植物多连发事件，机枪的多发不在这里
	/// @param 植物ID
	/// @return False则跳过原版发射（包括+58=0的发射与重置+58、原版双发、猫、裂荚等植物的双发）
	class PlantShootMultipleEvent : public BoolDLLEventTemplate<0x45F8AD, 5, 0x45F97B,REG_ESI>
	{
	public:
		PlantShootMultipleEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		PlantShootMultipleEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		PlantShootMultipleEvent() : PlantShootMultipleEvent("onPlantShootMultiple") {};
	};
	/// @brief 投手类植物跳过被多投标记的僵尸事件
	/// @param 植物ID(ECX)，僵尸ID(ESI)
	/// @return False则跳过该僵尸
	class PlantPultSkipEvent : public BoolDLLEventTemplate<0x4677E9, 6, 0x467881, REG_ESI, REG_ECX>
	{
	public:
		PlantPultSkipEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		PlantPultSkipEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		PlantPultSkipEvent() : PlantPultSkipEvent("onPlantPultSkip") {};
	};
	/// @brief 植物更新Shooting事件，发生在更新+90计时前
	/// @param 植物ID
	/// @return False则跳过原版更新，注意更新计时、重置豌豆头部动画等也会被跳过
	class PlantUpdateShootingEvent : public BoolDLLEventTemplate<0x464889, 6, 0x464D9F, REG_EDI>
	{
	public:
		PlantUpdateShootingEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		PlantUpdateShootingEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		PlantUpdateShootingEvent() : PlantUpdateShootingEvent("onPlantUpdateShooting") {};
	};
	/// @brief 植物开火事件。
	/// @note 此事件与 PlantShootEvent 注入位置相同，区别在于此事件可以选择跳过原版开火
	/// @param 触发事件的植物、开火目标僵尸、Weapon类型
	/// @return False则跳过原版开火
	class PlantFireEvent : public BoolDLLEventTemplate<0x466E0D, 6, 0x466E7A, REG_EBX, MEM_ESP_ADD(0x50), REG_EBP>
	{
	public:
		PlantFireEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		PlantFireEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		PlantFireEvent() : PlantFireEvent("onPlantFire") {};
	};
	/// @brief 植物开火生成子弹前的事件。
	/// @param 触发事件的植物、子弹类型、子弹初始化坐标X、Y
	/// @return False则跳过子弹生成
	/// @deprecated 请使用 PVZEvent::PlantFireEvent
	class PlantAddProjectileBeforeEvent : public BoolDLLEventTemplate<0x4672A5, 5, 0x467319, REG_ESI,REG_EDI,REG_EAX,REG_EBP>
	{
	public:
		PlantAddProjectileBeforeEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		PlantAddProjectileBeforeEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		PlantAddProjectileBeforeEvent() : PlantAddProjectileBeforeEvent("onPlantAddProjectileBefore") {};
	};
	/// @brief 四个投手的多投事件
	/// @param 植物ID（EDI） 植物副武器（ESI）
	class PlantPultMultipleEvent : public DLLEventTemplate<0x464C1C, 5, REG_ESI, REG_EDI>
	{
	public:
		PlantPultMultipleEvent(const char* str) : DLLEventTemplate() { Init(str); };
		PlantPultMultipleEvent(int address) : DLLEventTemplate() { Init(address); };
		PlantPultMultipleEvent() : PlantPultMultipleEvent("onPlantPultMultiple") {};
	protected:
		virtual void InitExtra(AsmBuilder& builder)
		{
			builder.popad().push_imm32(0x464C34).ret();
		}
	};
	/// @brief 总绘制事件，位置在绘制金钱框函数里
	/// @param Graphics*(REG_EDI)和Board*(REG_EDX)
	class BoardDrawImageEvent : public DLLEventTemplate<0x41A2B9, 6, REG_EDX, REG_EDI>
	{
	public:
		BoardDrawImageEvent(const char* str) : DLLEventTemplate() { Init(str); };
		BoardDrawImageEvent(int address) : DLLEventTemplate() { Init(address); };
		BoardDrawImageEvent() : BoardDrawImageEvent("onBoardDrawImage") {};
	};
	/// @brief 创建动画图集事件
	/// @param 触发事件的动画类型，触发事件的动画定义
	/// @return 是否生成动画图集
	class CreateAtlasEvent : public BoolDLLEventTemplate<0x471A96, 7, 0x471AFC, REG_ESI, REG_EAX>
	{
	public:
		CreateAtlasEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		CreateAtlasEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		CreateAtlasEvent() : CreateAtlasEvent("onCreateAtlas") {};
	};

	/// @brief 僵尸碾压植物事件
	/// @note 僵王踩踏和砸车暂时不触发此事件。
	/// @param 触发事件的僵尸，被碾压的行数，被碾压的列数，僵尸攻击类型，被碾压的植物
	/// @return 是否继续结算碾压。若取消，碾压不会发生。
	class ZombieSquishPlantEvent : public BoolDLLEventTemplate<0x52E971, 9, 0x52E980, REG_ECX, MEM_ESP_ADD(0x40),
		MEM_ESP_ADD(0x3C), MEM_ESP_ADD(0x44), REG_EDI>
	{
	public:
		ZombieSquishPlantEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		ZombieSquishPlantEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		ZombieSquishPlantEvent() : ZombieSquishPlantEvent("onZombieSquishPlant") {};
	};

	/// @brief 子弹初始化完成事件
	/// @note 此时 ImageX 和 ImageY 均未初始化
	/// @param 触发事件的子弹
	class ProjectileInitAfterEvent : public DLLEventTemplate<0x46CA78, 5, REG_EBP>
	{
	public:
		ProjectileInitAfterEvent(const char* str) : DLLEventTemplate() { Init(str); };
		ProjectileInitAfterEvent(int address) : DLLEventTemplate() { Init(address); };
		ProjectileInitAfterEvent() : ProjectileInitAfterEvent("onProjectileInitAfter") {};
	};
};