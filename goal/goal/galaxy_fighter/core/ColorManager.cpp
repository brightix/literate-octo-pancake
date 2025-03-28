#include "pch.h"
#include "ColorManager.h"

ColorManager& ColorManager::Instance()
{
	static ColorManager instance;
	return instance;
}

//color.r, color.g, color.b, color.a
SDL_Color& ColorManager::getColor(ColorType colorType) {
	int n = colorList.size();
	if (0 <= colorType && colorType < n) {
		return colorList[colorType];
	}
	return colorList[DefaultColor];
}

ColorManager::ColorManager() {
	colorList.resize(ColorCount);

	colorList[DefaultColor] = { 255,255,255,255 };
	colorList[CollisionColor] = { 255,255,0,255 };
	colorList[AttackColor] = { 255,0,0,255 };
	colorList[SubLineColor] = { 0,191,255,50 };
	colorList[System_Grey] = {127,127,127,100};
}
