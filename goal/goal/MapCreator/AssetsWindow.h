#pragma once
#include "CreatorComponent.h"
#include "./CreatorElements/ScrollBar.h"
#include "CreatorCamera/CreatorCamera.h"

class Asset:
    public CreatorElements
{
    shared_ptr<SDL_Texture> texture;
    string name;
    SDL_FRect worldRect;
    SDL_FRect showRect;
    SDL_FRect ClippedRect;
public:
    Asset(shared_ptr<SDL_Texture> texture,string name) : texture(texture),name(name){}

    void SetWorldRect(SDL_FRect rect) {
        worldRect = rect;
    }

    void SetShowRect(SDL_FRect rect) {
        showRect = rect;
    }

    void SetClippedRect(SDL_FRect rect) {
        ClippedRect = rect;
    }

    void get() {
        
    }

    void Update() override {
        if (texture) {

            //SDL_Color color = ColorManager::Instance().getColor(System_GreyWhite);
            //SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
            //SDL_RenderFillRect(r, &showRect);
            SDL_RenderTexture(r, texture.get(), &ClippedRect, &showRect);
        }
        else {
            SDL_Color color = ColorManager::Instance().getColor(System_GreyWhite);
            SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(r,&showRect);
        }
    }

    void DrawTex(SDL_FRect* src,SDL_FRect* dst) {
        SDL_RenderTexture(r, texture.get(), src, &showRect);
    }

    const SDL_FRect& getWorldRect() {
        return worldRect;
    }
    const SDL_FRect& getShowRect() {
        return showRect;
    }
    const string& getName() {
        return name;
    }
    SDL_Texture* getTexture() {
        return texture.get();
    }
};

class AssetsWindow :
    public CreatorComponent
{
    SDL_FRect contentRect;
    //ScrollBar_hor scrollBar_hor;
    std::unique_ptr<ScrollBar_ver> scrollBar_ver;
    bool isSliding = false;

    float scrollSpeed = 50;

    float initialMouseY = 0.0f;
    float initialViewportY = 0.0f;
    std::vector<Asset> assets;



    int rowItemCount = 4;
    float padding = 100;
    float ElementMaxWidth = 100;
    float ElementMaxHeight = 100;
    SDL_FRect ItemRect;

public:

    AssetsWindow(SDL_FRect placeholder);
    void RefreshAttr();
    void Update() override ;
    void UpdateInput();
    void UpdateAssets();
    void refreshAssets();
    void Reassign();
    void reCalculateAsstesShowRect();
    const SDL_FRect& GetContentRect();
    const SDL_FRect& GetViewport();
private:
};


