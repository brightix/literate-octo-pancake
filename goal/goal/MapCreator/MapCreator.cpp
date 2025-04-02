#include "pch.h"
#include "MapCreator.h"
#include "CreatorDebug/CreatorDebug.h"
#include "EventSystem/Events/SwitchHoveringWindow.h"
int CheckBoxIdAdder = 0;


static string CursorOnWindow = "";
void MapCreator::Update()
{
	CreatorDebug debug;

	Timer& timer = Timer::Instance();
	SDL_Renderer* r = RendererManager::Instance().getRenderer();
	InputManager& input = InputManager::Instance();
	bool running = true;
	while (running) {

		/* 事件刷新 */
		timer.update();
		HandleEvent(input,running);
		auto [mouseX, mouseY] = input.getMousexy();

		/* 渲染 */
		SDL_RenderClear(r);

		for (auto component : components) {
			component->Update();
			checkCursorPos(component, { mouseX,mouseY });
		}

		timer.showFps();


		debug.printText("CursorOnWindow", CursorOnWindow, {100.f,100.f});
		debug.printMouseXY({ (int)mouseX,(int)mouseY });
		SDL_RenderPresent(r);



		timer.sleep(timer.getRefreshTime());
	}
}

float getDimension(SDL_FRect& rect,const string& dimension) {
	return float();
}

void MapCreator::HandleEvent(InputManager& input,bool& running) {
	input.postUpdate();
	while (SDL_PollEvent(&event)) {
		if (!input.update(event)) {
			running = false;
			break;
		}
	}
	publisher.processEvents();
}

void MapCreator::checkCursorPos(CreatorComponent* component,SDL_FPoint pos) {
	if (SDL_PointInRectFloat(&pos,&component->GetWindowShowRect()) && component->GetComponentName()!= CursorOnWindow) {
		publisher.queueEvent(new SwitchHoveringWindow(component->GetComponentName()));
	}	
}

void MapCreator::onEvent(Event* event) {

	if (auto* switchHoveringWindow = dynamic_cast<SwitchHoveringWindow*>(event)) {
		CursorOnWindow = switchHoveringWindow->WindowName;
	}
}

MapCreator::MapCreator(SDL_FRect rect) {
	WindowId = WindowIdAdder++;

	publisher.subscribe(typeid(SwitchHoveringWindow),this);

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
