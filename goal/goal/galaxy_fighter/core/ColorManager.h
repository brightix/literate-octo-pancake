#pragma once
#include "pch.h"

enum ColorType {


	DefaultColor,
	//��ɫ
	CollisionColor,
	//��ɫ
	AttackColor,
	//��ɫ
	SubLineColor,
	//

	//�߼���
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