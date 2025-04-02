#pragma once
#include "CreatorElements.h"
#include "../CreatorComponent.h"
class ScrollBar :
    public CreatorElements
{
    CreatorComponent* father;
    SDL_FRect placeholder;
    SDL_FRect showRect_ver;
    SDL_FRect slider_ver;

    SDL_FRect showRect_hor;
    SDL_FRect slider_hor;
    SDL_FRect triangleUp;
    SDL_FRect triangleDown;
    float border = 10;

    bool isVerSliding = false;
    bool isHorSliding = false;

    float initialMouseY;
    float initialViewportY; 

    float initialMouseX;
    float initialViewportX;
    SDL_Renderer* r = RendererManager::Instance().getRenderer();
public:
    ScrollBar(CreatorComponent* father);
    void Update();
    float verUpdate(SDL_FPoint mousePos, bool isClicked, float viewportY, bool& isChanged);
    float horUpdate(SDL_FPoint mousePos, bool isClicked, float viewportY, bool& isChanged);
    std::pair<bool, SDL_FPoint> CheckSliding(SDL_FPoint mousePos, bool isClicked, SDL_FPoint viewport);
    void ShowVer();
    void ShowHor();
    void showScroll(SDL_FRect& slider);
    const SDL_FRect& getVerRect();
    const SDL_FRect& getHorRect();
    void refreshAttr();
};



















class ScrollBar_hor :
    public CreatorElements
{
    CreatorComponent* father;
    SDL_FRect placeholder;
    SDL_FRect slider;
    SDL_FRect triangleUp;
    SDL_FRect triangleDown;
    float border = 10;
public:
    ScrollBar_hor(CreatorComponent* father, SDL_FRect placeholder);
    void Update();
    void init();
};



