#pragma once
#include "pch.h"
#include "../BaseObject.h"
//#include "playerObject.h"

class PlayerObject;

class AttackBox :
    public BaseObject
{
    Rect hitBox;
    PlayerObject* from;
    SDL_Texture* texture;
    float actionTime = 0.0f;
    bool isHitGround = false;
public:
    AttackBox(PlayerObject* from,std::string attackType);
    void on_collision(BaseObject* other) override ;

    void update();
    void render();
    Rect* getHitBox();
    std::shared_ptr<SDL_FRect> getRenderRect();
    bool hasMoved() { return false; }
    bool shouldDelete() override;
    ~AttackBox() { std::cout << "AttackBox has been deleted" << std::endl; }
};

