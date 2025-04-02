#include "pch.h"
#include "CreatorElements.h"


class MapTile
    : public CreatorElements
{
    SDL_Renderer* renderer;
    std::shared_ptr<SDL_Texture> texture;
    SDL_FRect srcRect;
    SDL_FRect dstRect;
    std::pair<float,float> dragRatio;
public:
    MapTile(SDL_Renderer* renderer, shared_ptr<SDL_Texture> texture) :renderer(renderer), texture(texture) {
        srcRect = { 0.f,0.f,static_cast<float>(texture->w),static_cast<float>(texture->h) };
        dstRect = {0.f,0.f,srcRect.w,srcRect.h};
    }
    void Update() override {
        SDL_RenderTexture(renderer, texture.get(), &srcRect, &dstRect);
    }


    void Move(SDL_FPoint pos) {
        dstRect.x = pos.x;
        dstRect.y = pos.y;
    }

    void Drag(SDL_FPoint MousePos) {
        dstRect.x = MousePos.x - dstRect.w * dragRatio.first;
        dstRect.y = MousePos.y - dstRect.h * dragRatio.second;
        Update();
    }


    void SetSrcRect(SDL_FRect rect) {
        srcRect = rect;
    }
    void SetDstRect(SDL_FRect rect) {
        dstRect = rect;
    }
    void SetDragRatio(float RatioX,float RatioY) {
        dragRatio.first = RatioX;
        dragRatio.second = RatioY;
    }
    const SDL_FRect& GetSrc() {
        return srcRect;
    }
    const SDL_FRect& GetDst() {
        return dstRect;
    }
    SDL_Texture* GetTexture() {
        return texture.get();
    }
};