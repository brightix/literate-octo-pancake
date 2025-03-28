#pragma once
#include "pch.h"
#include "WorldWindow.h"
#include "ToolsWindow.h"
#include "AssetsWindow.h"
class MapCreator
{
	SDL_FRect WindowRect;
	WorldWindow* worldWindow;
	ToolsWindow* toolsWindow;
	AssetsWindow* assetsWindow;
public:
	MapCreator();
	~MapCreator();

	void Update();

private:
	void init();
};

