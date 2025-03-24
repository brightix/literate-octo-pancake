#include "pch.h"
#include "rendererManager.h"

RendererManager& RendererManager::Instance() {
	static RendererManager instance;
	return instance;
}
SDL_Renderer* RendererManager::getRenderer() { return renderer; }

SDL_Window* RendererManager::getWindow() { return window; }

void RendererManager::setWindowSize(float newWidth,float newHeight) {
	SDL_SetWindowSize(window, newWidth, newHeight);
}


bool RendererManager::init(SDL_Window* window) {
	if (!window) return false;
	renderer = SDL_CreateRenderer(window, "opengl");
	return renderer != nullptr;
}
void RendererManager::cleanUP() {
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
}

void RendererManager::renderTexture(const std::string& catalog,const std::string& fileName) {
	SDL_FRect rect = { 0,0,0,0 };
	shared_ptr<SDL_Texture> texture = ResourceManager::Instance().getTexture(catalog, fileName);
	SDL_GetTextureSize(texture.get(), &rect.w, &rect.h);
	SDL_RenderTexture(renderer, texture.get(), nullptr, &rect);
}

void RendererManager::renderTexture(const std::string& catalog, const std::string& fileName,int location) {
	SDL_FRect window = Resolution::Instance().getWindowRect();
	float x, y, w, h;
	shared_ptr<SDL_Texture> texture = ResourceManager::Instance().getTexture(catalog, fileName);
	SDL_GetTextureSize(texture.get(), &w, &h);

	switch (location) {
	case 0:
		x = 0, y = 0;
		break;
	case 1:
		x = window.w - w, y = 0;
		break;
	case 2:
		x = 0, y = window.h - h;
		break;
	case 3:
		x = window.w - w, y = window.h - h;
		break;
	default:
		x = 0, y = 0;
	}

	SDL_FRect rect = { x,y,w,h };

	SDL_RenderTexture(renderer, texture.get(), nullptr, &rect);
}

void RendererManager::switchScreenDisplayMove() {
	if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN) {
		SDL_SetWindowFullscreen(window,0);
	}
	else {
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		SDL_SetRenderLogicalPresentation(renderer,1920,1080, SDL_LOGICAL_PRESENTATION_LETTERBOX);
	}

}


RendererManager::RendererManager(){
	renderer = nullptr;
	auto& win = Resolution::Instance().getWindowRect();
	window = SDL_CreateWindow("���Ӷ������´�����ڶ�·��", win.w, win.h, SDL_WINDOW_MAXIMIZED);//SDL_WINDOW_MAXIMIZED
	init(window);
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
}

RendererManager::~RendererManager(){
	//ResourceManager::Instance().shutdown();
	SDL_DestroyWindow(window);
	cleanUP();
	cout << "��Ⱦ�������ѹر�" << endl;
}