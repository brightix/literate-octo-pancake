#pragma once
class CreatorComponent
{
protected:
	SDL_FRect placeholderRect = {0.0f, 0, 100,100};
	SDL_FRect showRect = { 0.0f,0,100,100 };
	SDL_Color color = { 255,255,255,255 };
	SDL_Renderer* r = RendererManager::Instance().getRenderer();
public:
	CreatorComponent(SDL_FRect& rect) : placeholderRect(rect) ,showRect(rect){}
	virtual void Update() = 0;
	void DrawBackground() {
		SDL_SetRenderDrawColor(r, 55, 55, 55, 255);
		SDL_RenderFillRect(r, &placeholderRect);
		SDL_SetRenderDrawColor(r, 22, 22, 22, 255);
		SDL_RenderFillRect(r, &showRect);
		SDL_RenderRect(r, &placeholderRect);

	}
	void DrawSubBorder(SDL_FRect& rect) {
		auto color = ColorManager::Instance().getColor(DefaultColor);
		SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
		SDL_RenderRect(r, &rect);
	}
	virtual SDL_FRect getContentRect() {
		return placeholderRect;
	}
	virtual SDL_FRect getViewport() {
		return {0,0,0,0};
	}
	virtual SDL_FRect getShowRect() {
		return showRect;
	}
};

