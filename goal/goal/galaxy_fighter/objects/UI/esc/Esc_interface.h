#pragma once
#include "../component.h"
class Esc_interface :
    public component
{
    SDL_Color backgroundColor;
public:
    Esc_interface();
    void render() override;
    bool update() override;
};

