#pragma once
#include "playerObject.h"
#include "SpritePlayer.h"

class Player_GreenTofu :
    public PlayerObject
{
    double animationtime;
    bool isFacingLeft;
    SDL_Texture* texture;

    std::unordered_map<PlayerState, SpriteSheet> spriteSheet;
    std::unordered_map<PlayerState, double> actionFrameDelay;
    void init();
public:
    Player_GreenTofu();

    void update();
};

