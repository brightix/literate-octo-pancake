#include "pch.h"
#include "MapCreator.h"

MapCreator::MapCreator() {
	InputManager::Instance().switchToEnglishInput();
	init();
}

void MapCreator::Update()
{
	Timer& timer = Timer::Instance();
	SDL_Renderer* r = RendererManager::Instance().getRenderer();
	InputManager& input = InputManager::Instance();
	bool running = true;
	while (running) {
		timer.update();
		SDL_Event event;
		input.postUpdate();
		while (SDL_PollEvent(&event)) {
			if (!input.update(event)) {
				running = false;
				break;
			}
		}
		SDL_RenderClear(r);

		toolsWindow->Update();

		assetsWindow->Update();
		worldWindow->Update();
		timer.showFps();
		SDL_RenderPresent(r);



		timer.sleep(timer.getRefreshTime());
	}
}


void MapCreator::init()
{
	this->WindowRect = Resolution::Instance().getWindowRect();
	SDL_FRect ToolsRect = { 0,0,300,WindowRect.h };
	SDL_FRect WorldRect = { ToolsRect.w,0,WindowRect.w - ToolsRect.w,300 };
	SDL_FRect AssetsRect = { ToolsRect.w,WorldRect.h,WorldRect.w,WindowRect.h - WorldRect.h };
	worldWindow =  new WorldWindow(WorldRect);
	assetsWindow = new AssetsWindow(AssetsRect);
	toolsWindow = new ToolsWindow(ToolsRect);
}

MapCreator::~MapCreator() {
	delete worldWindow;
	delete assetsWindow;
	delete toolsWindow;
}
