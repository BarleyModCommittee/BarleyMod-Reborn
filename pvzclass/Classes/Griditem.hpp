#pragma once
#include "../PVZ.h"
#include "Board.hpp"

namespace PVZ
{
	/// @brief 各种场地物件的基类。
	class Griditem : public BaseClass
	{
	public:
		/// @brief 场地物件的内存占用字节数。\n
		///		若派生类需要对应扩指针的对象，请在派生类中修改此数值。
		static const DWORD MemSize = 0x0EC;
		/// @brief 默认的场地物件类型，派生类需要定义同名常量，用于在 Board::GetAllGriditems() 中定向获取场地物件。
		static const GriditemType::GriditemType ItemType = GriditemType::None;
		Griditem(int indexoraddress);
		/// @brief 获取场地物件所在的 Board
		/// @return 场地物件所在的 Board
		PVZ::Board GetBoard();
		/// @brief 场地物件类型
		T_PROPERTY(GriditemType::GriditemType, Type, __get_Type, __set_Type, 0x8);
		/// @brief 场地物件状态
		T_PROPERTY(GriditemState::GriditemState, State, __get_State, __set_State, 0xC);
		/// @brief 列
		INT_PROPERTY(Column, __get_Column, __set_Column, 0x10);
		/// @brief 行
		INT_PROPERTY(Row, __get_Row, __set_Row, 0x14);
		/// @brief 绘制图层编号
		INT_PROPERTY(Layer, __get_Layer, __set_Layer, 0x1C);
		/// @brief 是否已消失
		/// @attention 你应该通过 Remove() 移除一个场地物件，而不是通过修改此变量。
		T_PROPERTY(BOOLEAN, NotExist, __get_NotExist, __set_NotExist, 0x20);
		/// @brief 识别 ID
		INT_READONLY_PROPERTY(Id, __get_Id, 0xE8);
		READONLY_PROPERTY_BINDING(int, __get_Index, Id & 0xFFFF) Index;
		/// @brief 移除此物件
		void Remove();
	};
	/// @brief 墓碑
	class Grave :public PVZ::Griditem
	{
	public:
		static const GriditemType::GriditemType ItemType = GriditemType::Grave;
		Grave(int indexoraddress) :Griditem(indexoraddress) {};
		INT_PROPERTY(AppearedValue, __get_AppearedValue, __set_AppearedValue, 0x18);
	};
	/// @brief 弹坑
	class Crater :public PVZ::Griditem
	{
	public:
		static const GriditemType::GriditemType ItemType = GriditemType::Crater;
		Crater(int indexoraddress) :Griditem(indexoraddress) {};
		/// @brief 消失倒计时
		INT_PROPERTY(DisappearCountdown, __get_DisappearCountdown, __set_DisappearCountdown, 0x18);
	};
	/// @brief 水族馆模式的脑子
	class AquariumBrain :public PVZ::Griditem
	{
	public:
		static const GriditemType::GriditemType ItemType = GriditemType::AquariumBrain;
		AquariumBrain(int indexoraddress) :Griditem(indexoraddress) {};
		/// @brief 实际的 X 坐标
		T_PROPERTY(FLOAT, X, __get_X, __set_X, 0x24);
		/// @brief 实际的 Y 坐标
		T_PROPERTY(FLOAT, Y, __get_Y, __set_Y, 0x28);
	};
	/// @brief 禅境花园的蜗牛
	class Snail :public PVZ::Griditem
	{
	public:
		static const GriditemType::GriditemType ItemType = GriditemType::Snail;
		Snail(int indexoraddress) :Griditem(indexoraddress) {};
		/// @brief 实际的 X 坐标
		T_PROPERTY(FLOAT, X, __get_X, __set_X, 0x24);
		/// @brief 实际的 Y 坐标
		T_PROPERTY(FLOAT, Y, __get_Y, __set_Y, 0x28);
		/// @brief 目标 X 坐标
		T_PROPERTY(FLOAT, TargetX, __get_TargetX, __set_TargetX, 0x2C);
		/// @brief 目标 Y 坐标
		T_PROPERTY(FLOAT, TargetY, __get_TargetY, __set_TargetY, 0x30);
	};
	/// @brief 罐子
	class Vase :public PVZ::Griditem
	{
	public:
		static const GriditemType::GriditemType ItemType = GriditemType::Vase;
		Vase(int indexoraddress) :Griditem(indexoraddress) {};
		/// @brief 罐子外观。本质是场地物件的状态。
		T_PROPERTY(VaseSkin::VaseSkin, Skin, __get_Skin, __set_Skin, 0xC);
		/// @brief 内含的僵尸类型
		T_PROPERTY(ZombieType::ZombieType, ContentZombie, __get_ContentZombie, __set_ContentZombie, 0x3C);
		/// @brief 内含的种子卡片类型
		T_PROPERTY(SeedType::SeedType, ContentPlant, __get_ContentPlant, __set_ContentPlant, 0x40);
		/// @brief 罐子实际含有的物品类型
		T_PROPERTY(VaseContent::VaseContent, Content, __get_Content, __set_Content, 0x44);
		/// @brief 是否高亮
		T_READONLY_PROPERTY(BOOLEAN, MouseEnter, __get_MouseEnter, 0x48);
		/// @brief 透明状态倒计时
		INT_PROPERTY(TransparentCountDown, __get_TransparentCountDown, __set_TransparentCountDown, 0x4C);
		/// @brief 储存阳光数
		INT_PROPERTY(Sun, __get_Sun, __set_Sun, 0x50);
		/// @brief 直接开启此罐子
		void Open();
	};
	/// @brief IZ 模式的脑子
	class IZBrain :public PVZ::Griditem
	{
	public:
		static const GriditemType::GriditemType ItemType = GriditemType::IZBrain;
		IZBrain(int indexoraddress) :Griditem(indexoraddress) {};
		/// @brief 脑子剩余生命值
		INT_PROPERTY(Hp, __get_Hp, __set_Hp, 0x18);
		/// @brief X 坐标
		T_PROPERTY(FLOAT, X, __get_X, __set_X, 0x24);
		/// @brief Y 坐标
		T_PROPERTY(FLOAT, Y, __get_Y, __set_Y, 0x28);
	};
	/// @brief 传送门
	/// @note 非传送门关卡，传送门只有画面效果，不会触发传送，\n
	///		因此此类只提供几个方法用于模拟传送门关卡中的传送效果
	class Portal :public PVZ::Griditem
	{
	public:
		Portal(int indexoraddress) :Griditem(indexoraddress) {};
		/// @brief 关闭此传送门
		void Close();
		/// @brief 判定僵尸是否进入这个传送门
		/// @param zombie 被判定的僵尸
		/// @return 僵尸是否进入传送门
		/// @todo 实现一个参数为 PVZ::Zombie 的版本
		bool isZombieIn(std::shared_ptr<PVZ::Zombie> zombie);
		/// @brief 获取僵尸从这个传送门出来时的X坐标
		/// @return 僵尸从这个传送门出来时的X坐标
		int getZombieOutX();
		/// @brief 判定子弹是否进入这个传送门
		/// @param projectile 被判定的子弹
		/// @return 子弹是否进入这个传送门
		bool isProjectileIn(std::shared_ptr<PVZ::Projectile> projectile);
		/// @brief 获取子弹从这个传送门射出时的X坐标
		/// @param 子弹从这个传送门射出时的X坐标
		int getProjectileOutX();
	};
	/// @brief 椭圆形传送门，颜色为蓝框冒白光
	class CirclePortal : public Portal
	{
	public:
		static const GriditemType::GriditemType ItemType = GriditemType::PortalBlue;
		CirclePortal(int indexoraddress) : Portal(indexoraddress) {};
	};
	/// @brief 矩形传送门，颜色为黄框
	class SquarePortal : public Portal
	{
	public:
		static const GriditemType::GriditemType ItemType = GriditemType::PortalYellow;
		SquarePortal(int indexoraddress) : Portal(indexoraddress) {};
	};
}