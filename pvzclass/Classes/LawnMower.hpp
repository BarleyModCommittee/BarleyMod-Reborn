#pragma once
#include "../PVZ.h"

namespace PVZ
{
	/// @brief 除草机
	class LawnMower : public BaseClass
	{
	public:
		/// @brief 除草机的内存占用字节数。\n
		///		若派生类需要对应扩指针的对象，请在派生类中修改此数值。
		static const DWORD MemSize = 0x48;
		LawnMower(int indexoraddress);
		/// @brief X 坐标
		T_PROPERTY(FLOAT, X, __get_X, __set_X, 8);
		/// @brief Y 坐标
		T_PROPERTY(FLOAT, Y, __get_Y, __set_Y, 0xC);
		/// @brief 绘制图层编号
		INT_PROPERTY(Layer, __get_Layer, __set_Layer, 0x10);
		/// @brief 行
		INT_PROPERTY(Row, __get_Row, __set_Row, 0x14);
		/// @brief 获取除草机的动画
		/// @return 除草机的动画
		PVZ::Animation GetAnimation();
		/// @brief 除草机状态
		T_PROPERTY(LawnmoverState::LawnmoverState, State, __get_State, __set_State, 0x2C);
		/// @brief 是否已消失
		T_PROPERTY(BOOLEAN, NotExist, __get_NotExist, __set_NotExist, 0x30);
		/// @brief 是否可见
		T_PROPERTY(BOOLEAN, Visible, __get_Visible, __set_Visible, 0x31);
		/// @brief 除草机类型
		T_PROPERTY(LawnmoverType::LawnmoverType, Type, __get_Type, __set_Type, 0x34);
		/// @brief Y 坐标偏移量
		T_PROPERTY(FLOAT, YOffset, __get_YOffset, __set_YOffset, 0x38);
		/// @brief 识别 ID
		INT_READONLY_PROPERTY(Id, __get_Id, 0x44);
		READONLY_PROPERTY_BINDING(int, __get_Index, Id & 0xFFFF) Index;
		/// @brief 移除该除草机
		void Die();
	};
	using Lawnmover = LawnMower;
}