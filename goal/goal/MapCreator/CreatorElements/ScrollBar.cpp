#include "pch.h"
#include "ScrollBar.h"


void ScrollBar_ver::Update() {
	SDL_FRect contentRect = father->getContentRect();
	float father_content_h = contentRect.h;
	SDL_FRect viewport = father->getViewport();

	verUpdate();
	horUpdate();

	DrawSubBorder(slider_ver);
	DrawSubBorder(slider_hor);
}

void ScrollBar_ver::verUpdate() {
	SDL_FRect contentRect = father->getContentRect();
	SDL_FRect viewport = father->getViewport();
	if (contentRect.h > viewport.h) {
		const float minSliderHeight = 20.0f;
		slider_ver.h = max(showRect_ver.h * viewport.h / contentRect.h, minSliderHeight);
		slider_ver.y = showRect_ver.y + showRect_ver.h * (viewport.y - contentRect.y) / (contentRect.h - viewport.h);

		slider_ver.y = std::clamp(slider_ver.y, showRect_ver.y, showRect_ver.y + showRect_ver.h - slider_ver.h);
		showScroll(slider_ver);
	}
}

void ScrollBar_ver::horUpdate() {
	SDL_FRect contentRect = father->getContentRect();
	SDL_FRect viewport = father->getViewport();
	if (contentRect.w > viewport.w) {
		slider_hor.w = showRect_hor.w * viewport.w / contentRect.w;
		slider_hor.y = showRect_hor.y + showRect_hor.w * (contentRect.x - viewport.x);
		showScroll(slider_hor);
	}
}

void ScrollBar_ver::showScroll(SDL_FRect& slider) {
	SDL_Color color = ColorManager::Instance().getColor(System_Grey);
	SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
	SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(r,&slider);
}

const SDL_FRect& ScrollBar_ver::getVerRect() {
	return slider_ver;
}

void ScrollBar_ver::init() {
	triangleUp.w = showRect_ver.w;
	triangleUp.h = 3 * border;

	triangleDown.w = showRect_ver.w;
	triangleDown.h = 3 * border;
}
ScrollBar_ver::ScrollBar_ver(CreatorComponent* father) : father(father){
	SDL_FRect fatherShowRect = father->getShowRect();
	placeholder = {
		fatherShowRect.x+ fatherShowRect.w - 5*border,
		fatherShowRect.y,
		5*border,
		fatherShowRect.h
	};
	showRect_ver = { placeholder.x + border, placeholder.y + border ,placeholder.w - 2 * border ,placeholder.h - 2 * border };
	slider_ver = showRect_ver;

	placeholder = {
		fatherShowRect.x,
		fatherShowRect.y + fatherShowRect.h - 5*border,
		fatherShowRect.w,
		5*border
	};
	showRect_hor = { placeholder.x + border, placeholder.y + border ,placeholder.w - 2 * border ,placeholder.h - 2 * border };
	slider_hor = showRect_hor;


	//triangleUp = placeholder;
	//triangleDown = placeholder;
	init();
}