#include "../../pch.h"
#include "RendererManager.h"

RendererManager& RendererManager::instance() { static RendererManager instance;return instance; }

RendererManager::RendererManager() {
	SDL_Window win = 
	renderer = SDL_GetRenderer();
}

RendererManager::~RendererManager()
{

	std::cout << "��Ⱦ������" << std::endl;
}
