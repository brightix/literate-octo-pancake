#pragma once
#include "CreatorComponent.h"

class ToolsWindow :
    public CreatorComponent
{
public:
    ToolsWindow() = default;
    ToolsWindow(SDL_FRect& rect) : CreatorComponent(rect) {
        float border = 25;
        windowShowRect.x += border;
        windowShowRect.y += border;
        windowShowRect.w -= 2 * border;
        windowShowRect.h -= 2 * border;
    }
    void Update();
};

