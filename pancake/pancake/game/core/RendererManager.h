#pragma once
class RendererManager
{
	RendererManager& instance();
private:
	RendererManager();
	~RendererManager();
	SDL_Renderer* renderer;
};

