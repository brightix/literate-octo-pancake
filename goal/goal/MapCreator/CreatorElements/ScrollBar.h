#pragma once
#include "CreatorElements.h"
#include "../CreatorComponent.h"
class ScrollBar_ver :
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

    SDL_Renderer* r = RendererManager::Instance().getRenderer();
public:
    ScrollBar_ver(CreatorComponent* father);
    void Update();
    void verUpdate();
    void horUpdate();
    void showScroll(SDL_FRect& slider);
    const SDL_FRect& getVerRect();
    void refreshAttr();
    void init();
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



