#pragma once
#include "../PVZ.h"

namespace PVZ
{
	class PVZApp;

	/// @brief 控制音乐相关内容的类
	/// @todo 完善 doxygen 注释
	class Music : public BaseClass
	{
	public:
		Music(int address) : BaseClass(address) {};
		PROPERTY(MusicType::MusicType, __get_Type, __set_Type) Type;
		//MINGAM_ENABLE or MINGAM_DISABLE
		INT_PROPERTY(INGAMEable, __get_INGAMEable, __set_INGAMEable, 0x10);
		//MINGAME_STARTED or MINGAME_NOTSTARTED
		INT_PROPERTY(INGAMEStart, __get_INGAMEStart, __set_INGAMEStart, 0x18);
		INT_READONLY_PROPERTY(Tempo, __get_Tempo, 0x1C);
		INT_READONLY_PROPERTY(Ticks_Row, __get_Ticks_Row, 0x20);
		T_PROPERTY(INGAMEState::INGAMEState, State, __get_State, __set_State, 0x24);
		INT_PROPERTY(AttributeCountdown, __get_AttributeCountdown, __set_AttributeCountdown, 0x28);
		T_PROPERTY(INGAMEEffect::INGAMEEffect, INGAMEEffect, __get_INGAMEEffect, __set_INGAMEEffect, 0x2C);
	};

	Music GetMusic();
}
