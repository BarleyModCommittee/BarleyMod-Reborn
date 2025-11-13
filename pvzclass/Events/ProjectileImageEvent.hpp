#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief ProjectileImageEvent 处理函数的参数之一的类型
	enum ProjectileImgParam
	{
		/// @brief 获取的子弹绘制图片的行数
		PROJECTILE_IMAGEROW,
		/// @brief 获取子弹对应的图片基址
		PROJECTILE_IMAGE,
	};

	/// @brief 子弹绘制图片事件。
	/// @param 子弹基址、ProjectileImgParam
	/// @return 图片对象的基址（或图片的行数）。若返回值为负数，则使用默认数值。
	class ProjectileImageEvent
	{
	private:
		class ImgRow : public IntDLLEventTemplate<0x46E6FA, 7, 0, 0,
			0, REG_EAX, false, CONST_VAL(PROJECTILE_IMAGEROW), REG_ESI>
		{
		public:
			ImgRow(const char* str) : IntDLLEventTemplate() { Init(str); };
			ImgRow(int address) : IntDLLEventTemplate() { Init(address); };
		};
		class Img : public IntDLLEventTemplate<0x46E6C7, 5, 0, 0,
			0, MEM_ESP_ADD(0x2C), false, CONST_VAL(PROJECTILE_IMAGE), REG_ESI>
		{
		public:
			Img(const char* str) : IntDLLEventTemplate() { Init(str); };
			Img(int address) : IntDLLEventTemplate() { Init(address); };
		};
		ImgRow* img_row;
		Img* image;
	public:
		ProjectileImageEvent()
		{
			const char* str = "GetProjectileImage";
			img_row = new ImgRow(str);
			image = new Img(str);
		}
		ProjectileImageEvent(int address)
		{
			img_row = new ImgRow(address);
			image = new Img(address);
		}
		void end()
		{
			img_row->end();
			image->end();
		}
	};
	/// @brief 子弹图片大小事件。默认获取的导出函数名为 GetProjectileImageSize 。
	/// @param 依次为：子弹基址、原始大小。
	/// @return 调整后的子弹图片大小。
	class ProjectileImageSizeEvent : public FloatDLLEventTemplate<0x46E6D3, 6, MEM_ESP_ADD(0x30), false,
		MEM_ESP_ADD(0x30), REG_ESI>
	{
	public:
		ProjectileImageSizeEvent(const char* str) : FloatDLLEventTemplate() { Init(str); };
		ProjectileImageSizeEvent(int address) : FloatDLLEventTemplate() { Init(address); };
		ProjectileImageSizeEvent() : ProjectileImageSizeEvent("GetProjectileImageSize") {};
	};
}