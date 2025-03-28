#pragma once
#include "CreatorComponent.h"

class ToolsWindow :
    public CreatorComponent
{
public:
    ToolsWindow() = default;
    ToolsWindow(SDL_FRect& rect) : CreatorComponent(rect) {
        float border = 25;
        showRect.x += border;
        showRect.y += border;
        showRect.w -= 2 * border;
        showRect.h -= 2 * border;
    }
    void Update();
};

