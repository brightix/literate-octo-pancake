#include "pch.h"
#include "Resolution.h"

Resolution& Resolution::getInstance() {
	static Resolution instance;
	return instance;
}

Resolution::Resolution() {
	curRes = 2;
	
	resolution = { { 720, 405 }, { 1280,720 }, { 1920,1080 }, {2560,1440} };
	isLandScape = true;
}

Resolution::~Resolution()
{
	cout << "�ֱ��ʵ����ѹر�" << endl;
}

void Resolution::setResolution(short level) { 
	curRes = level;
	SDL_SetWindowSize(RendererManager::getInstance().getWindow(), resolution[level].first, resolution[level].second);
	windowRect.w = resolution[level].first;
	windowRect.h = resolution[level].second;
	cout << "�ֱ��ʸ���Ϊ" << window_width << "x" << window_height << endl;

}

std::pair<float, float> Resolution::getResolution() {
	return resolution[curRes];
}

SDL_FRect& Resolution::getWindowRect() {
	return windowRect;
}

void Resolution::setLandScape(bool b) { isLandScape = b; }

bool Resolution::getIsLandScape() { return isLandScape; }

float Resolution::getScaleFactor() {
	return 	getResolution().first/1080;
}

