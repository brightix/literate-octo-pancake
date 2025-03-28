#pragma once
#include "pch.h"
#include "../component.h"

class UIManager
{
private:
	std::vector<component*> uiStack;
public:
	static UIManager& Instance();

	void pushUI(component* ui);

	void popUI();

	void refreshEscButton();
	void EscUIHasPushed();

	bool isUiStackEmpty();
	void update();


	bool IsQuit();
	
	
	
	UIManager(const UIManager&) = delete;
	UIManager& operator=(const UIManager&) = delete;
private:
	UIManager() = default;
	~UIManager() = default;
	bool escUIHasPushed = false;
};

