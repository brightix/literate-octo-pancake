#pragma once
#include "PlayerObject.h"

class Player_lion :
    public PlayerObject
{
    SDL_Texture* texture;
public:
    Player_lion();
    void update();
};

