#pragma once
#include "DLLEvent.h"

/// @brief 植物被点击事件。
/// @note 只有主键和中键点击会触发事件。
/// @note 优先级低于原版的玉米炮选中。
/// @param 依次为：触发事件的植物、点击时的鼠标 X 坐标、点击时的鼠标 Y 坐标。
class PlantMouseDownEvent : public DLLEventTemplate<0x466413, 5, MEM_ESP_ADD(0x2C), MEM_ESP_ADD(0x2C), REG_ESI>
{
public:
	PlantMouseDownEvent(const char* str) : DLLEventTemplate() { Init(str); };
	PlantMouseDownEvent(int address) : DLLEventTemplate() { Init(address); };
	PlantMouseDownEvent() : PlantMouseDownEvent("onPlantMouseDown") {};
};