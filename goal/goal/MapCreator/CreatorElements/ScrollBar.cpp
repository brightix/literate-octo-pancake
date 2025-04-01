#include "pch.h"
#include "ScrollBar.h"


void ScrollBar_ver::Update() {
	refreshAttr();
	SDL_FRect contentRect = father->GetPlaceholderRect();
	float father_content_h = contentRect.h;
	SDL_FRect viewport = father->GetViewport();

	verUpdate();
	//horUpdate();

	DrawSubBorder(slider_ver);
	DrawSubBorder(slider_hor);
}

void ScrollBar_ver::verUpdate() {
	SDL_FRect contentRect = father->GetPlaceholderRect();
	SDL_FRect viewport = father->GetViewport();
	SDL_FRect windowShowRect = father->GetWindowShowRect();
	if (contentRect.h > viewport.h) {
		const float minSliderHeight = 20.0f;

		slider_ver.h = max(showRect_ver.h * viewport.h / contentRect.h, minSliderHeight);
		
		float scrollPresent = (viewport.y - contentRect.y) / (contentRect.h - viewport.h);
		//scrollPresent = clamp(scrollPresent,0.f,1.f);
		//滚动条的位置等于 = 滑轨最大可移动长度 / ( (当前视口坐标 - 内容起始坐标) / (视口最大可移动长度) )
		slider_ver.y = showRect_ver.y + (showRect_ver.h - slider_ver.h) * scrollPresent;

		showScroll(slider_ver);
	}
}

void ScrollBar_ver::horUpdate() {
	SDL_FRect contentRect = father->GetContentRect();
	SDL_FRect viewport = father->GetViewport();
	if (contentRect.w >= viewport.w) {
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

void ScrollBar_ver::refreshAttr() {
	SDL_FRect fatherShowRect = father->GetWindowShowRect();
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
}

ScrollBar_ver::ScrollBar_ver(CreatorComponent* father) : father(father){
	refreshAttr();
	//triangleUp = placeholder;
	//triangleDown = placeholder;
}

