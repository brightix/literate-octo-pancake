#pragma once
#include "pch.h"



class RendererManager {
public:
	static RendererManager& getInstance();

	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();

	bool init(SDL_Window* window);
	void cleanUP();


	RendererManager(const RendererManager&) = delete;
	RendererManager& operator=(const RendererManager&) = delete;
private:
	RendererManager();
	~RendererManager();
	SDL_Renderer* renderer;
	SDL_Window* window;

};