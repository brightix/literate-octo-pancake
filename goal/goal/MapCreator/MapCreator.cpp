#include "pch.h"
#include "MapCreator.h"
#include "CreatorDebug/CreatorDebug.h"

int CheckBoxIdAdder = 0;



void MapCreator::Update()
{
	CreatorDebug debug;

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
		auto [mouseX, mouseY] = input.getMousexy();
		SDL_RenderClear(r);

		for (auto component : components) {
			component->Update();
		}

		timer.showFps();

		debug.printMouseXY({ mouseX,mouseY });
		SDL_RenderPresent(r);

		timer.sleep(timer.getRefreshTime());
	}
}

float getDimension(SDL_FRect& rect,const string& dimension) {
	return float();
}

MapCreator::MapCreator(SDL_FRect rect) {
	WindowId = WindowIdAdder++;

	/* 全屏 */
	//RendererManager::Instance().switchScreenDisplayMove();
	auto& renderer = RendererManager::Instance();
	auto& res = Resolution::Instance();
	SDL_SetWindowBordered(renderer.getWindow(), true);
	res.setResolution(2);
	//SDL_SetWindowResizable(window,true);



	InputManager::Instance().switchToEnglishInput();
	placeholderRect = rect;
	auto WindowRect = res.getWindowRect();

	/* 初始化组件 */
	SDL_FRect ToolsRect = { 0,0,WindowRect.w * 0.2f,WindowRect.h };
	SDL_FRect WorldRect = { ToolsRect.w,0,WindowRect.w - ToolsRect.w,WindowRect.h * 0.8f };
	SDL_FRect AssetsRect = { ToolsRect.w,WorldRect.h,WorldRect.w,WindowRect.h - WorldRect.h };



	components.push_back(new ToolsWindow(ToolsRect));
	components.push_back(new WorldWindow(WorldRect));
	components.push_back(new AssetsWindow(AssetsRect));
}

MapCreator::~MapCreator() {
	delete worldWindow;
	delete assetsWindow;
	delete toolsWindow;
}
