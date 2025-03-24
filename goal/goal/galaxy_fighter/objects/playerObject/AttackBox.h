#pragma once
#include "pch.h"
#include "../BaseObject.h"
class AttackBox :
    public BaseObject
{
    Rect hitBox;
    BaseObject* from;
    SDL_Texture* texture;
    float actionTime = 0.0f;
public:
    AttackBox(BaseObject* from,std::string attackType,SDL_FRect rect);
    void on_collision(std::shared_ptr<BaseObject> other) override ;

    void update();
    void render();
    Rect* getHitBox();
    std::shared_ptr<SDL_FRect> getRenderRect();
    bool hasMoved() { return false; }
    bool shouldDelete() override;
};

