#include "pch.h"
#include "Resolution.h"

Resolution& Resolution::Instance() {
	static Resolution instance;
	return instance;
}

Resolution::Resolution() {

	curRes = 0;
	
	resolution = { { 720, 405 }, { 1280,720 }, { 1920,1080 }, {2560,1440} };
	isLandScape = true;
	windowRect = {0,0,1920,1080};
}

Resolution::~Resolution()
{
	cout << "分辨率单例已关闭" << endl;
}

void Resolution::setResolution(short level) { 
	curRes = level;
	SDL_SetWindowSize(RendererManager::Instance().getWindow(), resolution[level].first, resolution[level].second);
	windowRect.w = resolution[level].first;
	windowRect.h = resolution[level].second;
	Camera::Instance().setViewport(windowRect);

	cout << "分辨率更改为" << windowRect.w << "x" << windowRect.h << endl;

}

SDL_FRect& Resolution::getWindowRect() {
	return windowRect;
}

void Resolution::setLandScape(bool b) { isLandScape = b; }

bool Resolution::getIsLandScape() { return isLandScape; }

float Resolution::getScaleFactor() {
	return 	windowRect.h/1080.0f;
}

