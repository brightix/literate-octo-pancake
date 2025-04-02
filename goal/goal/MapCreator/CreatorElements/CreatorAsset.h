#pragma once
#include "pch.h"
#include "CreatorElements.h"
#include "MapTile.h"


class Asset :
    public CreatorElements
{
    std::shared_ptr<SDL_Texture> texture;
    std::string name;
    SDL_FRect worldRect;
    SDL_FRect showRect;
    SDL_FRect ClippedRect;
    double pressedTime = 0.0;
    bool isDrag;
    SDL_FRect dragPos;
    //std::pair<float, float> dragRatio;
public:
    Asset(shared_ptr<SDL_Texture> texture, string name) : texture(texture), name(name), isDrag(false), dragPos({0.f,0.f,static_cast<float>(texture->w),static_cast<float>(texture->h)}) {}



    void Update() override {
        auto& input = InputManager::Instance();
        bool isClicked = input.isMouseButtonPressed(SDL_BUTTON_LEFT);
        if (isDrag) {
            auto [x, y] = input.getMousexy();
            if (isClicked) {
                Drag(x,y);
            }
            else isDrag = false;
        }
        else  if (dragPos.x != showRect.x || dragPos.y != showRect.y) {
            dragPos.x = showRect.x;
            dragPos.y = showRect.y;
            Rollback();
        }
        else {
            Display();
            float x, y;
            SDL_GetMouseState(&x, &y);
            if (IsPressedForAWhile(Timer::Instance().getDeltaAdjustTime(), {x, y}, isClicked)) {
                isDrag = true;
                SetDragPos({x,y});
            }
        }
    }

    //void DrawTex(SDL_FRect* src, SDL_FRect* dst) {
    //    SDL_RenderTexture(r, texture.get(), src, &showRect);
    //}

    bool IsPressedForAWhile(double time,SDL_FPoint pos,bool isClicked) {
        if (SDL_PointInRectFloat(&pos, &showRect) && isClicked) {
            pressedTime += time;
        }
        else {
            pressedTime = 0.f;
        }
        return pressedTime >= 0.1f;
    }

    MapTile* GenerateMapTileWhenPressed() {
        return new MapTile(RendererManager::Instance().getRenderer(), texture);
    }

    void Drag(float x,float y) {
        dragPos.x = x;
        dragPos.y = y;
        if (texture) {
            SDL_RenderTexture(r, texture.get(), nullptr, &dragPos);
        }
        else {
            SDL_Color color = ColorManager::Instance().getColor(System_GreyWhite);
            SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(r, &dragPos);
        }
    }

    void Rollback() {

    }
    void Display() {
        if (texture) {
            SDL_RenderTexture(r, texture.get(), &ClippedRect, &showRect);
        }
        else {
            SDL_Color color = ColorManager::Instance().getColor(System_GreyWhite);
            SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(r, &showRect);
        }
    }
    //void SetDragRatio(float RatioX, float RatioY) {
    //    dragRatio.first = RatioX;
    //    dragRatio.second = RatioY;
    //}


    void onEvent(Event* event) {
        
    }

    void StartDrag() {
        isDrag = true;
    }

    void SetWorldRect(SDL_FRect rect) {
        worldRect = rect;
    }

    void SetShowRect(SDL_FRect rect) {
        showRect = rect;
        dragPos.x = showRect.x;
        dragPos.y = showRect.y;
    }

    void SetClippedRect(SDL_FRect rect) {
        ClippedRect = rect;
    }
    void SetDragPos(SDL_FPoint pos) {
        dragPos.x = pos.x;
        dragPos.y = pos.y;
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