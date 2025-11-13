#pragma once
#include "DLLEvent.h"

/// @brief 僵尸啃食植物事件
/// @param 触发事件的僵尸和植物
class ZombieEatEvent : public DLLEventTemplate<0x52FB40, 7, REG_ECX, REG_EDI>
{
public:
	ZombieEatEvent() : DLLEventTemplate() { Init("onZombieEat"); };
	ZombieEatEvent(const char* str) : DLLEventTemplate() { Init(str); };
	ZombieEatEvent(int address) : DLLEventTemplate() { Init(address); };
};

namespace PVZEvent
{
	/// @brief 掉头僵尸判断啃食事件
	/// @param 触发事件的僵尸
	/// @return 僵尸是否可以啃食
	class ZombieNoHeadEatEvent
	{
	private:
		class Part1 : public DiversionEventTemplate<0x52BD13, 7, 0x52BD20, 0x52BE4E, REG_EDI>
		{
		public:
			Part1(int address) : DiversionEventTemplate() { Init(address); };
		} *p1;
		class Part2 : public DiversionEventTemplate<0x52F629, 6, 0x52F635, 0x52F6BC, REG_EDI>
		{
		public:
			Part2(int address) : DiversionEventTemplate() { Init(address); };
		} *p2;
	public:
		ZombieNoHeadEatEvent() : ZombieNoHeadEatEvent("IsZombieNoHeadEat") {};
		ZombieNoHeadEatEvent(const char* name) : ZombieNoHeadEatEvent(PVZ::Memory::GetProcAddress(name)) {};
		ZombieNoHeadEatEvent(int address)
		{
			p1 = new Part1(address);
			p2 = new Part2(address);
		}
		void end()
		{
			p1->end();
			p2->end();
		}
	};
}