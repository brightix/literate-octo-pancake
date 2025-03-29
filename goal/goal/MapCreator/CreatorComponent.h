#pragma once
class CreatorComponent
{
protected:
	SDL_FRect placeholderRect = {0.0f, 0, 100,100};
	SDL_FRect windowShowRect = { 0.0f,0,100,100 };
	SDL_Color color = { 255,255,255,255 };
	SDL_Renderer* r = RendererManager::Instance().getRenderer();
public:
	CreatorComponent(SDL_FRect& rect) : placeholderRect(rect) , windowShowRect(rect){}
	virtual void Update() = 0;
	void DrawBackground() {
		SDL_SetRenderDrawColor(r, 55, 55, 55, 255);
		SDL_RenderFillRect(r, &placeholderRect);
		SDL_SetRenderDrawColor(r, 22, 22, 22, 255);
		SDL_RenderFillRect(r, &windowShowRect);
		SDL_RenderRect(r, &placeholderRect);

	}
	void DrawSubBorder(SDL_FRect& rect) {
		auto color = ColorManager::Instance().getColor(DefaultColor);
		SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
		SDL_RenderRect(r, &rect);
	}
	void DrawSubFillRect(SDL_FRect& rect) {
		auto color = ColorManager::Instance().getColor(DefaultColor);
		SDL_SetRenderDrawBlendMode(r,SDL_BLENDMODE_NONE);
		SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(r, &rect);
	}
	virtual const SDL_FRect& getContentRect() {
		return placeholderRect;
	}
	virtual const SDL_FRect& getViewport() {
		static SDL_FRect emptyViewport = {0.f,0.f,0.f,0.f};
		return emptyViewport;
	}
	virtual const SDL_FRect& getWindowShowRect() {
		return windowShowRect;
	}
};

