#pragma once
#include "pch.h"
class CreatorElements
{
protected:
	SDL_Renderer* r = RendererManager::Instance().getRenderer();
public:
	CreatorElements() = default;
	virtual void Update() = 0;
	void DrawSubBorder(SDL_FRect& rect) {
		auto color = ColorManager::Instance().getColor(DefaultColor);
		SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
		SDL_RenderRect(r, &rect);
	}
};

