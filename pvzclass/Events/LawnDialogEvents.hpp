#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief LawnDialog 加入管理器事件
	/// @note 此时 LawnDialog 已经加入自带的所用控件。
	/// @param 触发事件的 LawnDialog
	class LawnDialogAdd2ManagerEvent : public DLLEventTemplate<0x4571A5, 5, REG_ESI>
	{
	public:
		LawnDialogAdd2ManagerEvent(int address) : DLLEventTemplate() { Init(address); };
		LawnDialogAdd2ManagerEvent(const char* name) : DLLEventTemplate() { Init(name); };
		LawnDialogAdd2ManagerEvent() : LawnDialogAdd2ManagerEvent("onLawnDialogAdd2Manager") {};
	};

	/// @brief LawnDialog 移出管理器事件
	/// @note 此时 LawnDialog 已经移出自带的所用控件。
	/// @param 触发事件的 LawnDialog
	class LawnDialogRemoveFromManagerEvent : public DLLEventTemplate<0x457226, 5, REG_ESI>
	{
	public:
		LawnDialogRemoveFromManagerEvent(int address) : DLLEventTemplate() { Init(address); };
		LawnDialogRemoveFromManagerEvent(const char* name) : DLLEventTemplate() { Init(name); };
		LawnDialogRemoveFromManagerEvent() : LawnDialogRemoveFromManagerEvent("onLawnDialogRemoveFromManager") {};
	};

	/// @brief LawnDialog 构建事件
	/// @note 此时 LawnDialog 已经完成自带内容的构建。
	/// @param 触发事件的 LawnDialog
	class LawnDialogConstructEvent : public DLLEventTemplate<0x456E5D, 5, REG_EBP>
	{
	public:
		LawnDialogConstructEvent(int address) : DLLEventTemplate() { Init(address); };
		LawnDialogConstructEvent(const char* name) : DLLEventTemplate() { Init(name); };
		LawnDialogConstructEvent() : LawnDialogConstructEvent("onLawnDialogConstruct") {};
	};

	/// @brief LawnDialog 销毁事件
	/// @note 此时 LawnDialog 已经销毁自带控件。
	/// @param 触发事件的 LawnDialog
	class LawnDialogDestructEvent : public DLLEventTemplate<0x456EA0, 7, REG_ECX>
	{
	public:
		LawnDialogDestructEvent(int address) : DLLEventTemplate() { Init(address); };
		LawnDialogDestructEvent(const char* name) : DLLEventTemplate() { Init(name); };
		LawnDialogDestructEvent() : LawnDialogDestructEvent("onLawnDialogDestuct") {};
	};
}
