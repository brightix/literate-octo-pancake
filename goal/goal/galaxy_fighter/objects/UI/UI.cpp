#include "pch.h"
#include "UI.h"

UI::UI()
{
	texture = ResourceManager::Instance().getTexture("","").get();
	windowRect = Resolution::Instance().getWindowRect();
	components.emplace_back(new Esc_button());
}

UI_State UI::getState()
{
	return state;
}

void UI::update()
{
	for (auto component : components) {
		component->update();
	}
}

