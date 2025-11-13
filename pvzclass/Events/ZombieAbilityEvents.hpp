#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	namespace Dancer
	{
		/// @brief 舞王开始召唤僵尸事件
		/// @param 触发事件的舞王僵尸
		/// @return 是否进行此次召唤
		class SummonStartEvent : public BoolDLLEventTemplate<0x528970, 10, 0x52BA3D, REG_ESI>
		{
		public:
			SummonStartEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
			SummonStartEvent(int address) : BoolDLLEventTemplate() { Init(address); };
			SummonStartEvent() : SummonStartEvent("onDancerSummonStart") {};
		};
	}
	namespace Digger
	{
		/// @brief 矿工僵尸丢失镐子事件
		/// @param 触发事件的矿工僵尸
		class LoseAxeAfterEvent : public DLLEventTemplate<0x5282FE, 5, REG_ESI>
		{
		public:
			LoseAxeAfterEvent(const char* str) : DLLEventTemplate() { Init(str); };
			LoseAxeAfterEvent(int address) : DLLEventTemplate() { Init(address); };
			LoseAxeAfterEvent() : LoseAxeAfterEvent("onDiggerLoseAxeAfter") {};
		};
	}
	namespace Ladder
	{
		/// @brief 扶梯僵尸搭梯后事件
		/// @param 触发事件的僵尸
		/// @return 是否失去防具
		class PlaceLadderAfterEvent : public BoolDLLEventTemplate<0x52AA1A, 5, 0x52AA1F, REG_EBX>
		{
		public:
			PlaceLadderAfterEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
			PlaceLadderAfterEvent(int address) : BoolDLLEventTemplate() { Init(address); };
			PlaceLadderAfterEvent() : PlaceLadderAfterEvent("onLadderPlacedAfter") {};
		};

		/// @brief 扶梯僵尸搭梯后事件
		/// @param 触发事件的僵尸、僵尸生成的梯子
		class PlaceLadderEvent : public DLLEventTemplate<0x52A9FD, 5, REG_EAX, REG_EBX>
		{
		public:
			PlaceLadderEvent(const char* str) : DLLEventTemplate() { Init(str); };
			PlaceLadderEvent(int address) : DLLEventTemplate() { Init(address); };
			PlaceLadderEvent() : PlaceLadderEvent("onLadderPlaced") {};
		};
	}
}
