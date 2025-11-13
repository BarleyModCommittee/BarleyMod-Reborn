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
				BYTE code[] = { MOV_PTR_ADDR_EUX(REG_ESI, 0x525884) };
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
			Catapult2(const char* str) : Catapult2(PVZ::Memory::GetProcAddress(str)) {};
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

	/// @brief 僵尸动画速度随 buff 改变事件
	/// @param 触发事件的僵尸，僵尸的基础动画速度
	/// @return 调整后的僵尸动画速度
	class ZombieSpeedAlterEvent : public DLLEvent
	{
	public:
		ZombieSpeedAlterEvent(int address)
		{
			hookAddress = 0x52F026;
			rawlen = 5;
			BYTE code[] =
			{
				PUSH_PTR_EUX_ADD_V(REG_ESI, 8),
				PUSH_EAX,
				INVOKE(address),
				FSTP_PTR_EUX_ADD_V(REG_ESI, 8),
				ADD_ESP(8)
			};
			start(STRING(code));
		}
		ZombieSpeedAlterEvent(const char* str) : ZombieSpeedAlterEvent(PVZ::Memory::GetProcAddress(str)) {};
		ZombieSpeedAlterEvent() : ZombieSpeedAlterEvent("CalcZombieSpeedAlter") {};
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

	/// @brief 植物开始眨眼事件
	/// @param 触发事件的植物，植物选择的目标僵尸，植物是否使用副武器
	class NormalPlantAttackStartEvent : public DLLEventTemplate<0x45EF3F, 6, MEM_ESP_ADD(0x3C), MEM_ESP_ADD(0x34), REG_ESI>
	{
	public:
		NormalPlantAttackStartEvent(const char* str) : DLLEventTemplate() { Init(str); };
		NormalPlantAttackStartEvent(int address) : DLLEventTemplate() { Init(address); };
		NormalPlantAttackStartEvent() : NormalPlantAttackStartEvent("onNormalPlantAttackStart") {};
	};
};