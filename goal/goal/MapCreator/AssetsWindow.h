#pragma once
#include "CreatorComponent.h"
#include "./CreatorElements/ScrollBar.h"
#include "CreatorCamera/CreatorCamera.h"
#include "CreatorElements/CreatorAsset.h"


class AssetsWindow :
    public CreatorComponent
{
    SDL_FRect contentRect;
    std::unique_ptr<ScrollBar> scrollBar;


    /* 选中的图标 */
    MapTile* MapTile;
    bool isDrag;

    float scrollSpeed = 50; 


    std::vector<Asset> assets;
    /* 排列图标 */
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


