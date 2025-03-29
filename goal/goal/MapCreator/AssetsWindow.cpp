#include "pch.h"
#include "AssetsWindow.h"
#include "CreatorDebug/CreatorDebug.h"

void AssetsWindow::Update()
{
	UpdateInput();
	DrawBackground();
	DrawSubBorder(placeholderRect);
	DrawSubBorder(windowShowRect);
	scrollBar_ver->Update();
	
	UpdateAssets();
}

void AssetsWindow::UpdateInput() {
	bool isScrolling = false;
    InputManager& input = InputManager::Instance();
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
	SDL_FRect slider = scrollBar_ver->getVerRect();
	if ((input.isCursorHovering(&slider) || isSliding) && input.isMouseButtonPressed(SDL_BUTTON_LEFT)) {//input.isMouseButtonPressed(SDL_BUTTON_LEFT)
		auto [x, y] = input.getMousexy();
		if (!isSliding) {
			isSliding = true;
			initialMouseY = static_cast<float>(y);
			initialViewportY = camera->getViewport().y;
		}
		float deltaY = y - initialMouseY;
		camera->setViewportXY(0,initialViewportY + deltaY);
		isScrolling = true;
	}
	else if (isSliding) {
		isSliding = false;
	}
	if (input.isKeyPressedOnce(SDL_SCANCODE_L)) {
		camera->setViewportXY(0,camera->getViewport().h * 2);
	}
	if (input.isKeyPressedOnce(SDL_SCANCODE_K)) {
		camera->setViewportXY(0, camera->getViewport().h / 2);
	}
	if (isScrolling) {

	}
	reCalculateAsstesShowRect();
}

void AssetsWindow::UpdateAssets() {
	CreatorDebug debug;
	for (auto& asset : assets) {
		SDL_FRect showRect = asset.getShowRect();
		if (camera->isOnScreen(showRect)) {
			asset.Update();
			debug.printInfo(asset.getName(),asset.getShowRect(),1);
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
	float rowLength = contentRect.w;
	float colItemGap = (rowLength - rowItemCount * ItemRect.w) / (rowItemCount + 1);
	int totalCount = static_cast<int>(assets.size());

	int n = (totalCount + rowItemCount - 1) / rowItemCount;

	for (int i = 0;i < n;i++) {
		ItemRect.y = padding + i * (ItemRect.h + padding);
		for (int j = 0;j < rowItemCount;j++) {
			int index = (i * rowItemCount) + j;
			if (index >= totalCount) break;
			ItemRect.x = padding + j * (ItemRect.w + padding);
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

const SDL_FRect& AssetsWindow::getContentRect()
{
	return contentRect;
}

const SDL_FRect& AssetsWindow::getViewport() {

	return camera->getViewport();
}

AssetsWindow::AssetsWindow(SDL_FRect& rect) : CreatorComponent(rect){
	float border = 25;
	windowShowRect.x += border;
	windowShowRect.y += border;
	windowShowRect.w -= 2 * border;
	windowShowRect.h -= 2 * border;

	contentRect = {0.f,0.f, windowShowRect.w * 1.f,windowShowRect.h * 1.5f };

	SDL_FRect viewport = {0,0,windowShowRect.w,windowShowRect.h};
	camera = make_unique<CreatorCamera>(viewport);
	
    camera->setCameraRange(&contentRect);
	ItemRect = {0,0,0,0};
	refreshAssets();
	scrollBar_ver = make_unique<ScrollBar_ver>(this);
}
