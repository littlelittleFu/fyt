#pragma once

namespace DATA
{
	struct RegionCommon
	{
		std::string        KeyName;
		uint32_t      left;
		uint32_t      top;
		uint32_t      width;
		uint32_t      height;
		uint32_t		top2;
		uint32_t		left2;
		int32_t		BorderStyle;
		uint32_t		RenderType;	//绘制图片时使用的叠加方式 0:加亮BLEND_ONE(src)-BLEND_ONE(dest) 1:正常
	};
}