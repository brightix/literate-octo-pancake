#pragma once
#include "pch.h"
#include "CreatorCamera/CreatorCamera.h"

extern int WindowIdAdder;
class CreatorComponent
{
protected:
	int WindowId;
	SDL_FRect placeholderRect = {0.0f, 0, 100,100};
	SDL_FRect contentRect = { 0.0f, 0, 100,100 };
	SDL_FRect windowShowRect = { 0.0f,0,100,100 };
	SDL_Color color = { 255,255,255,255 };
	SDL_Renderer* r = RendererManager::Instance().getRenderer();
	std::unique_ptr<CreatorCamera> camera;
	//int DivCount;
public:
	CreatorComponent(){}
	CreatorComponent(SDL_FRect placeholder){
		SetPlaceholderRect(placeholder);
	}
	virtual void Update() = 0;
	void DrawBackground() {
		//UpdateShowRect();
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
	void SetPlaceholderRectX(float val) {
		placeholderRect.x = val;
		UpdateShowRect();
	}
	void SetPlaceholderRectY(float val) {
		placeholderRect.y = val;
		UpdateShowRect();
	}
	void SetPlaceholderRectW(float val) {
		placeholderRect.w = val;
		UpdateShowRect();
	}
	void SetPlaceholderRectH(float val) {
		placeholderRect.h = val;
		if (camera) {
			camera->setViewportWH(camera->GetViewport().w, val);
		}
	}
	virtual void UpdateShowRect() {
		float border = 25;
		int idx = 7;
		windowShowRect.x = placeholderRect.x + border;
		windowShowRect.y = placeholderRect.y + border;
		windowShowRect.w = placeholderRect.w - 2 * border;
		windowShowRect.h = placeholderRect.h - 2 * border;
		if (camera) {
			auto viewport = camera->GetViewport();
			float showAspectRatio = windowShowRect.w / windowShowRect.h; // UI 显示区域的比例
			float newViewportW, newViewportH;

			// 获取 viewport 的短边
			float shortSide = min(viewport.w, viewport.h);

			// 让短边决定长边，避免宽高比失调
			if (viewport.w < viewport.h) {
				newViewportW = shortSide;
				newViewportH = shortSide / showAspectRatio;
			}
			else {
				newViewportH = shortSide;
				newViewportW = shortSide * showAspectRatio;
			}

			camera->setViewportWH(newViewportW, newViewportH);
		}

	}




	
	void SetPlaceholderRect(SDL_FRect rect) {
		placeholderRect = rect;
		UpdateShowRect();
	}

	void AddPlaceholderRect(float dx, float dy, float dw, float dh) {
		placeholderRect.x += dx;
		placeholderRect.y += dy;
		placeholderRect.w += dw;
		placeholderRect.h += dh;
	}



	virtual const SDL_FRect& GetPlaceholderRect() {
		return placeholderRect;
	}
	virtual const SDL_FRect& GetContentRect() {
		return contentRect;
	}
	virtual const SDL_FRect& GetViewport() {
		static SDL_FRect emptyViewport = {0.f,0.f,0.f,0.f};
		return emptyViewport;
	}
	virtual const SDL_FRect& GetWindowShowRect() {
		return windowShowRect;
	}
	virtual int GetUIName() {
		return WindowId;
	}
	//virtual const int& GetIncludeDivCount() {
	//	return DivCount;
	//}
};

class DefaultComponent : public CreatorComponent{

public:
	DefaultComponent() {}
	void Update() {

	}
};