#pragma once
#include "pch.h"
#include "component.h"
#include "esc/Esc_button.h"
enum componentType {
	UI_Time,
	UI_PlayerHealth,
	UI_PlayerPower,
	UI_Config
};

enum class UI_State {
	Esc_button,
	TAB,
	NONE
};

class UI
{
	SDL_Texture* texture;
	SDL_FRect windowRect;
	//std::vector<std::unique_ptr<component>> components;
	std::vector<component*> components;

	UI_State state;
	Esc_button esc_button;

public:
	UI();
	UI_State getState();
	void update();
};

