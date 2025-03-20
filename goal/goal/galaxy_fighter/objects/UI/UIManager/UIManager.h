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

	bool isUiStackEmpty();

	void update();
	UIManager(const UIManager&) = delete;
	UIManager& operator=(const UIManager&) = delete;
private:
	UIManager() = default;
	~UIManager() = default;
};

