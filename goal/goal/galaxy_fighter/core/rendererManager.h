#pragma once
#include "pch.h"



class RendererManager {
public:
	static RendererManager& Instance();

	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();

	void setWindowSize(float width, float height);

	bool init(SDL_Window* window);
	void cleanUP();

	void renderTexture(const std::string& catalog, const std::string& fileName);

	void renderTexture(const std::string& catalog, const std::string& fileName, int location);

	void switchScreenDisplayMove();


	RendererManager(const RendererManager&) = delete;
	RendererManager& operator=(const RendererManager&) = delete;
private:
	void changeScreenDisplayMode(bool b);
	RendererManager();
	~RendererManager();
	SDL_Renderer* renderer;
	SDL_Window* window;

};