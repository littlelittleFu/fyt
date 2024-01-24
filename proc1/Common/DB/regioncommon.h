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
		uint32_t		RenderType;	//����ͼƬʱʹ�õĵ��ӷ�ʽ 0:����BLEND_ONE(src)-BLEND_ONE(dest) 1:����
	};
}