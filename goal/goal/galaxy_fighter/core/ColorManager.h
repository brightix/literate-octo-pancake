#pragma once
#include "pch.h"

enum ColorType {


	DefaultColor,
	//黄色
	CollisionColor,
	//红色
	AttackColor,
	//蓝色
	SubLineColor,
	//

	//高级灰
	System_Grey,
	ColorCount
};

class ColorManager {
public:
	static ColorManager& Instance();
	SDL_Color& getColor(ColorType colorType);
	ColorManager(const ColorManager&) = delete;
	ColorManager& operator=(const ColorManager&) = delete;
private:
	ColorManager();
	std::vector<SDL_Color> colorList;
};