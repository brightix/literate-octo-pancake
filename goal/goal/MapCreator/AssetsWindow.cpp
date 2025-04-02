#include "pch.h"
#include "AssetsWindow.h"
#include "CreatorDebug/CreatorDebug.h"

void AssetsWindow::Update()
{

	InputManager& input = InputManager::Instance();
	RendererManager& renderer = RendererManager::Instance();
	auto [x, y] = input.getMousexy();
	CreatorDebug debug;
	UpdateInput();
	DrawBackground();
	DrawSubBorder(placeholderRect);
	DrawSubBorder(windowShowRect);
	UpdateAssets();
	scrollBar->Update();
	debug.printRectInfo("viewport",GetViewport(), GetPlaceholderRect(), 1);
	//if (MapTile) {
	//	MapTile->Drag({ x,y });
	//}
}

void AssetsWindow::UpdateInput() {
	bool isScrolling = false;
    InputManager& input = InputManager::Instance();
	RendererManager& renderer = RendererManager::Instance();
	auto [x, y] = input.getMousexy();
	bool isLeftBottonPressed = input.isMouseButtonPressed(SDL_BUTTON_LEFT);
    if (input.isCursorHovering(&windowShowRect)) {
        if (int dir = -input.isMouseWheelYScrolled()) {
			if (input.isKeyPressed(SDL_SCANCODE_LSHIFT)) {
				camera->addViewportXY(dir * scrollSpeed, 0);
			}
			else {
				camera->addViewportXY(0, dir * scrollSpeed);
			}
			isScrolling = true;
        }
    }
	auto [isChanged, newViewportPos] = scrollBar->CheckSliding({ x,y }, isLeftBottonPressed, { camera->GetViewport().x ,camera->GetViewport().y });
	if (isChanged) {
		camera->setViewportXY(newViewportPos.x, newViewportPos.y);
	}
	if (input.isKeyPressedOnce(SDL_SCANCODE_L)) {
		camera->setViewportXY(0,camera->GetViewport().h * 2);
	}
	if (input.isKeyPressedOnce(SDL_SCANCODE_K)) {
		camera->setViewportXY(0, camera->GetViewport().h / 2);
	}
	//if (MapTile && !isLeftBottonPressed) {
	//	delete MapTile;
	//	MapTile = nullptr;
	//}
	if (isScrolling || isChanged) {
		reCalculateAsstesShowRect();
	}
}

void AssetsWindow::UpdateAssets() {
	CreatorDebug debug;

	auto [x, y] = InputManager::Instance().getMousexy();
	for (auto& asset : assets) {
		SDL_FRect showRect = asset.getShowRect();
		SDL_FRect worldRect = asset.getWorldRect();
		if (camera->isOnScreen(worldRect)) {
			asset.Update();
		}
	}
}

void AssetsWindow::refreshAssets() {
	assets.push_back(Asset(ResourceManager::Instance().getTexture("gameLogo","logo_2.jpg"),"miniWorld"));
	assets.push_back(Asset(ResourceManager::Instance().getTexture("gameLogo", "logo_3.jpg"), "miniWorld"));
	assets.push_back(Asset(ResourceManager::Instance().getTexture("bk", "bk_3.jpg"), "miniWorld"));
	Reassign();
}

void AssetsWindow::Reassign() {
	float rowLength = windowShowRect.w;
	float colItemGap = (rowLength - rowItemCount * ItemRect.w) / (rowItemCount + 1);
	int totalCount = static_cast<int>(assets.size());

	int n = (totalCount + rowItemCount - 1) / rowItemCount;

	for (int i = 0;i < n;i++) {
		ItemRect.y = padding + i * (ItemRect.h + padding);
		for (int j = 0;j < rowItemCount;j++) {
			int index = (i * rowItemCount) + j;
			if (index >= totalCount) break;
			ItemRect.x = colItemGap + j * (ItemRect.w + colItemGap);
			SDL_GetTextureSize(assets[index].getTexture(),&ItemRect.w,&ItemRect.h);
			float scale;
			if (ItemRect.w > ItemRect.h) {
				scale = ElementMaxWidth / ItemRect.w;
			}
			else {
				scale = ElementMaxHeight / ItemRect.h;
			}
			ItemRect.w *= scale;
			ItemRect.h *= scale;
			assets[index].SetWorldRect(ItemRect);
		}
	}
	reCalculateAsstesShowRect();
	contentRect = {0,0,windowShowRect.w + 1000, padding + n * (ItemRect.h + padding) };
}

void AssetsWindow::reCalculateAsstesShowRect() {
	CreatorDebug debug;
	for (auto& asset : assets) {
		float texW, texH;
		SDL_GetTextureSize(asset.getTexture(), &texW, &texH);
		SDL_FRect worldRect = asset.getWorldRect();
		SDL_FRect clipped = camera->transformViewportArea(worldRect);

		SDL_FRect srcRect;
		srcRect.x = (clipped.x - worldRect.x) / worldRect.w * texW;
		srcRect.y = (clipped.y - worldRect.y) / worldRect.h * texH;
		srcRect.w = (clipped.w / worldRect.w) * texW;
		srcRect.h = (clipped.h / worldRect.h) * texH;

		asset.SetClippedRect(srcRect);
		asset.SetShowRect(camera->WorldToViewport_rect(windowShowRect, clipped));
	}
}

const SDL_FRect& AssetsWindow::GetContentRect()
{
	return contentRect;
}

const SDL_FRect& AssetsWindow::GetViewport() {

	return camera->GetViewport();
}

AssetsWindow::AssetsWindow(SDL_FRect placeholder) : CreatorComponent(placeholder) {
	WindowId = WindowIdAdder++;
	name = "AssetsWindow";

	SDL_FRect viewport = {0,0,windowShowRect.w,windowShowRect.h};
	camera = make_unique<CreatorCamera>(viewport);
	
    camera->setCameraRange(&contentRect);
	ItemRect = {0,0,ElementMaxWidth,ElementMaxHeight };
	refreshAssets();
	scrollBar = make_unique<ScrollBar>(this);
}

void AssetsWindow::RefreshAttr() {
	scrollBar->refreshAttr();
}