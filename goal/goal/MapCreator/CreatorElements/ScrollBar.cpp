#include "pch.h"
#include "ScrollBar.h"


void ScrollBar::Update() {
	bool isChanged = false;
	ShowHor();
	ShowVer();
	DrawSubBorder(slider_ver);
	DrawSubBorder(slider_hor);
}


std::pair<bool, SDL_FPoint> ScrollBar::CheckSliding(SDL_FPoint mousePos, bool isClicked, SDL_FPoint viewport){
	bool isChanged = false;
	
	if (!isHorSliding) {
		viewport.y = verUpdate(mousePos, isClicked, viewport.y, isChanged);
	}
	if (!isVerSliding) {
		viewport.x = horUpdate(mousePos, isClicked, viewport.x, isChanged);
	}
	return { isChanged,viewport };
}
float ScrollBar::verUpdate(SDL_FPoint mousePos,bool isClicked, float viewportY,bool& isChanged) {
	if (isClicked && (SDL_PointInRectFloat(&mousePos,&slider_ver) || isVerSliding)) {
		if (!isVerSliding) {
			isVerSliding = true;
			initialMouseY = mousePos.y;
			initialViewportY = viewportY;
		}
		float deltaY = mousePos.y - initialMouseY;
		viewportY = initialViewportY + deltaY;
		isChanged = true;

	}
	else if (isVerSliding) {
		isVerSliding = false;
	}
	return viewportY;
}

float ScrollBar::horUpdate(SDL_FPoint mousePos, bool isClicked, float viewportX, bool& isChanged) {
	if (isClicked && (SDL_PointInRectFloat(&mousePos, &slider_hor) || isHorSliding)) {
		if (!isHorSliding) {
			isHorSliding = true;
			initialMouseX = mousePos.x;
			initialViewportX = viewportX;
		}
		float deltaX = mousePos.x - initialMouseX;
		viewportX = initialViewportX + deltaX;
		isChanged = true;
	}
	else if (isHorSliding) {
		isHorSliding = false;
	}
	return viewportX;
}

void ScrollBar::ShowVer() {
	SDL_FRect contentRect = father->GetContentRect();
	SDL_FRect viewport = father->GetViewport();
	SDL_FRect windowShowRect = father->GetWindowShowRect();
	if (contentRect.h > viewport.h) {
		const float minSliderHeight = 20.0f;

		slider_ver.h = max(showRect_ver.h * viewport.h / contentRect.h, minSliderHeight);

		float scrollPresent = (viewport.y) / (contentRect.h - viewport.h);

		//滚动条的位置等于 = 滑轨最大可移动长度 / ( (当前视口坐标 - 内容起始坐标) / (视口最大可移动长度) )
		slider_ver.y = showRect_ver.y + (showRect_ver.h - slider_ver.h) * scrollPresent;

		showScroll(slider_ver);
	}
}

void ScrollBar::ShowHor() {
	SDL_FRect contentRect = father->GetContentRect();
	SDL_FRect viewport = father->GetViewport();
	SDL_FRect windowShowRect = father->GetWindowShowRect();

	if (contentRect.w > viewport.w) {
		const float minSliderHeight = 20.0f;

		slider_hor.w = max(showRect_hor.w * viewport.w / contentRect.w, minSliderHeight);

		float scrollPresent = viewport.x / (contentRect.w - viewport.w);

		//滚动条的位置等于 = 滑轨最大可移动长度 / ( (当前视口坐标 - 内容起始坐标) / (视口最大可移动长度) )
		slider_hor.x = showRect_hor.x + (showRect_hor.w - slider_hor.w) * scrollPresent;

		showScroll(slider_hor);
	}
}

void ScrollBar::showScroll(SDL_FRect& slider) {
	SDL_Color color = ColorManager::Instance().getColor(System_Grey);
	SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
	SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(r,&slider);
}



const SDL_FRect& ScrollBar::getVerRect() {
	return slider_ver;
}
const SDL_FRect& ScrollBar::getHorRect() {
	return slider_hor;
}

void ScrollBar::refreshAttr() {
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

//bool isHovering(SDL_F) {
//
//}
ScrollBar::ScrollBar(CreatorComponent* father) : father(father){
	refreshAttr();
}

