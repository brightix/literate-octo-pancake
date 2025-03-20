#pragma once
#include "../../BTNode.h"
class display_at_position :
    public BTNode
{
    std::shared_ptr<BaseObject> obj;
    shared_ptr<SDL_Texture> texture;
    shared_ptr<SDL_FRect> srcrect;
    shared_ptr<SDL_FRect> dstrect;
    double* angle;
    int* isFacingRight;
public:
    display_at_position(shared_ptr<SDL_Texture> texture, shared_ptr<SDL_FRect> srcrect, shared_ptr<SDL_FRect> dstrect, double* angle,int* isFacingRight);
    bool execute() override;
};

