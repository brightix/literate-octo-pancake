#pragma once
#include "CreatorComponent.h"

class ToolsWindow :
    public CreatorComponent
{
public:
    ToolsWindow(SDL_FRect placeholder);
    void Update();
};

