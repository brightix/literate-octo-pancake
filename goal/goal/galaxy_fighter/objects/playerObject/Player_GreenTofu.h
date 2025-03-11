#pragma once
#include "playerObject.h"

class Player_GreenTofu :
    public PlayerObject
{
    bool isFacingLeft;
    SDL_FRect srcRect;
    SDL_Texture* texture;
public:
    Player_GreenTofu();
    void update();
};

