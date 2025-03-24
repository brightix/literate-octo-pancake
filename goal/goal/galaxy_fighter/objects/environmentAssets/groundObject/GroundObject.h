#pragma once
#include "../../BaseObject.h"
#include "../../../core/physics/QuadTree.h"

class GroundObject :
    public BaseObject
{
private:
    std::shared_ptr<SDL_Texture> texture;
    std::shared_ptr<Rect> hitBox;
    std::shared_ptr<SDL_FRect> worldRect;
    std::shared_ptr<ParalleNode> root;
public:
    GroundObject(float x,float y,float scaleFactor);
    void update() override;
    void render() override;
    Rect* getHitBox() override ;
    std::shared_ptr<SDL_FRect> getRenderRect() override ;
    void on_collision(std::shared_ptr<BaseObject> other);
};

