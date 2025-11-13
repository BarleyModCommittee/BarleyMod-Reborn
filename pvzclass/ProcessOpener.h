#pragma once
#include <windows.h>
/// @brief 用于加载 PVZ 主程序的类。
class ProcessOpener
{
public:
	static LPCWSTR ProcessName;
	static LPCWSTR WindowTitle;
	static LPCWSTR Directory;
	static LPCWSTR ExecuteableName;
	/// @brief 根据进程名称寻找 PVZ 进程
	/// @param processName 进程名称
	/// @return 找到的 PVZ 进程 ID
	static DWORD OpenByProcessName(LPCWSTR processName);
	/// @brief 根据窗口标题寻找 PVZ 进程
	/// @param processName 窗口名称
	/// @return 找到的 PVZ 进程 ID
	static DWORD OpenByWindowTitle(LPCWSTR processName);
	/// @brief 根据给定的目录和可执行文件名称，打开文件并获得其进程 ID
	/// @param directory 文件所在文件夹目录
	/// @param executeableName 可执行文件名称
	/// @return 打开的 PVZ 进程 ID
	static DWORD OpenByFilePath(LPCWSTR directory, LPCWSTR executeableName);
	/// @brief 使用默认设置，尝试寻找 PVZ 进程
	/// @return 找到的 PVZ 进程 ID
	static DWORD Open();
};

