#pragma once
#include "CreatorComponent.h"
#include "./CreatorElements/ScrollBar.h"
#include "CreatorCamera/CreatorCamera.h"

class Asset:
    public CreatorElements
{
    shared_ptr<SDL_Texture> texture;
    string name;
public:
    Asset(shared_ptr<SDL_Texture> texture,string name) : texture(texture),name(name){}
    void Update() override {

        SDL_RenderTexture(r, texture.get(), nullptr, &showRect);
    }
};

class AssetsWindow :
    public CreatorComponent
{
    SDL_FRect contentRect;
    //ScrollBar_hor scrollBar_hor;
    std::unique_ptr<ScrollBar_ver> scrollBar_ver;
    bool isSliding = false;
    std::unique_ptr<CreatorCamera> camera;

    float scrollSpeed = 10;

    float initialMouseY = 0.0f;
    float initialViewportY = 0.0f;
    std::vector<Asset> assets;
public:

    AssetsWindow(SDL_FRect& rect);
    void Update() override ;
    void UpdateInput();
    void UpdateAssets();
    void refreshAssets();
    SDL_FRect getContentRect() override;
    SDL_FRect getViewport();
private:
};


