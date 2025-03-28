#include "pch.h"
#include "AssetsWindow.h"

void AssetsWindow::Update()
{
	UpdateInput();
	DrawBackground();
	DrawSubBorder(placeholderRect);
	DrawSubBorder(showRect);
	scrollBar_ver->Update();
	
	UpdateAssets();
}

void AssetsWindow::UpdateInput() {
    InputManager& input = InputManager::Instance();
    if (input.isCursorHovering(&showRect)) {
        if (int dir = input.isMouseWheelYScrolled()) {
			if (input.isKeyPressed(SDL_SCANCODE_LSHIFT)) {
				camera->addViewport(dir * scrollSpeed, 0);
			}
			else {
				camera->addViewport(0, dir * scrollSpeed);
			}
        }


    }
	SDL_FRect slider = scrollBar_ver->getVerRect();
	if ((input.isCursorHovering(&slider) || isSliding) && input.isMouseButtonPressed(SDL_BUTTON_LEFT)) {//input.isMouseButtonPressed(SDL_BUTTON_LEFT)
		auto [x, y] = input.getMousexy();
		if (!isSliding) {
			isSliding = true;
			initialMouseY = y;
			initialViewportY = camera->getViewport().y;
		}
		float deltaY = y - initialMouseY;
		camera->setViewport(0,initialViewportY + deltaY);
		cout << camera->getViewport().y << endl;
	}
	else if (isSliding) {
		isSliding = false;
	}
}

void AssetsWindow::UpdateAssets() {
	for (auto asset : assets) {
		asset.Update();
	}
}

void AssetsWindow::refreshAssets() {
	assets.push_back(Asset(ResourceManager::Instance().getTexture("gameLogo","logo_2.jpg"),"miniWorld",cameraviewport));
}
SDL_FRect AssetsWindow::getContentRect()
{
	return contentRect;
}

SDL_FRect AssetsWindow::getViewport() {
	return camera->getViewport();
}



AssetsWindow::AssetsWindow(SDL_FRect& rect) : CreatorComponent(rect){
	float border = 25;
	showRect.x += border;
	showRect.y += border;
	showRect.w -= 2 * border;
	showRect.h -= 2 * border;

	contentRect = showRect;
	contentRect.h *= 1.2;
	contentRect.w *= 2;
	scrollBar_ver = make_unique<ScrollBar_ver>(this);
	camera = make_unique<CreatorCamera>(showRect);
    camera->setCameraRange(&contentRect);
}
