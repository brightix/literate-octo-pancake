#pragma once
#include "playerObject.h"
#include "SpritePlayer.h"

class Player_GreenTofu :
    public PlayerObject
{
    double animationtime;
    bool isFacingLeft;
    SDL_FRect srcRect;
    SDL_Texture* texture;
public:
    Player_GreenTofu();
    void update();

    void refreshAnimationTime() override;
};

