#pragma once
#include "CreatorComponent.h"
#include "CreatorCamera/CreatorCamera.h"

typedef struct WorldTexture {
    WorldTexture(shared_ptr<SDL_Texture> texture,SDL_FRect rect) : texture(texture), rect(rect) {}
    shared_ptr<SDL_Texture> texture;
    SDL_FRect rect;
}WorldTexture;
class WorldWindow :
    public CreatorComponent
{
    float windowAreaScale = 1.0f;
    float scaleFactor = 1.0f;
    bool relativeMouseMode = false;
    SDL_FRect BaseViewport;
    SDL_FRect realMap;

public:
    WorldWindow(SDL_FRect placeholder);
    void Update();
    void UpdateAttr();
    void UpdateInput();
private:
    void DrawSubLine();
    void DrawInfo();
    void DrawTexture();
    std::vector<WorldTexture> textures;
};

