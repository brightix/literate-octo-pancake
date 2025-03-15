#pragma once
#include "pch.h"



class RendererManager {
public:
	static RendererManager& getInstance();

	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();

	bool init(SDL_Window* window);
	void cleanUP();

	void renderTexture(const std::string& catalog, const std::string& fileName);


	RendererManager(const RendererManager&) = delete;
	RendererManager& operator=(const RendererManager&) = delete;
private:
	RendererManager();
	~RendererManager();
	SDL_Renderer* renderer;
	SDL_Window* window;

};