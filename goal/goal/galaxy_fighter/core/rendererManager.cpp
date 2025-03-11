#include "pch.h"
#include "rendererManager.h"

RendererManager& RendererManager::getInstance() {
	static RendererManager instance;
	return instance;
}
SDL_Renderer* RendererManager::getRenderer() { return renderer; }

SDL_Window* RendererManager::getWindow() { return window; }

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



RendererManager::RendererManager(){
	renderer = nullptr;
	window = SDL_CreateWindow("menu", swidth, sheight, SDL_WINDOW_MAXIMIZED);
	init(window);
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
}
RendererManager::~RendererManager(){
	//ResourceManager::getInstance().shutdown();
	SDL_DestroyWindow(window);
	cleanUP();
	cout << "äÖÈ¾Æ÷µ¥ÀýÒÑ¹Ø±Õ" << endl;
}