#include "pch.h"
#include "CreatorCamera.h"

CreatorCamera::CreatorCamera(SDL_FRect viewport) : viewport(viewport) {}

void CreatorCamera::setViewport(float x,float y) {

    viewport.x = clamp(x,world->x,world->x + world->w - viewport.w);
    viewport.y = clamp(y, world->y, world->y + world->h - viewport.h);
}

void CreatorCamera::addViewport(float x, float y) {
    viewport.x += x;
    viewport.y += y;
}

SDL_FRect CreatorCamera::getViewport() { return viewport; }

void CreatorCamera::setCameraRange(SDL_FRect* Area) {
	world = Area;
}

SDL_FRect& CreatorCamera::getCameraRange() { return *world; }


bool CreatorCamera::isOnScreen(SDL_FRect& showRect, SDL_FRect& rect) {
    SDL_FRect screenRect = worldToViewport_rect(showRect, rect);
    return !(screenRect.x + screenRect.w < showRect.x ||
             screenRect.x > showRect.x + showRect.w ||
             screenRect.y + screenRect.h < showRect.y ||
             screenRect.y > showRect.y + showRect.h);
}

//rect.x, rect.y, rect.w, rect.h
SDL_FRect CreatorCamera::worldToViewport_rect(SDL_FRect& showRect, SDL_FRect rect) {
	return {
		showRect.x + (rect.x - viewport.x) * (showRect.w / viewport.w),
		showRect.y + (rect.y - viewport.y) * (showRect.h / viewport.h),
		rect.w * (showRect.w / viewport.w),
		rect.h * (showRect.h / viewport.h)
	};
}

SDL_FRect CreatorCamera::worldToViewport_line(SDL_FRect& showRect, SDL_FRect line) {
	return {	
		line.x - viewport.x + showRect.x,
		line.y - viewport.y + showRect.y,
		line.w - viewport.x + showRect.x,
		line.h - viewport.y + showRect.y };
}

SDL_FPoint CreatorCamera::worldToViewport_dot(SDL_FRect& showRect, SDL_FPoint worldPos) {
	return { 
		showRect.x + (worldPos.x - viewport.x) * (showRect.w / viewport.w),
		showRect.y + (worldPos.y - viewport.y) * (showRect.h / viewport.h) };
}

SDL_FRect CreatorCamera::transformViewportArea(SDL_FRect worldRect) {
    if (worldRect.x < viewport.x) {
        float diff = viewport.x - worldRect.x;
        worldRect.x = viewport.x;
        worldRect.w -= diff; // 减去被裁剪的部分
    }
    if (worldRect.y < viewport.y) {
        float diff = viewport.y - worldRect.y;
        worldRect.y = viewport.y;
        worldRect.h -= diff;
    }
    if (worldRect.x + worldRect.w > viewport.x + viewport.w) {
        worldRect.w = viewport.x + viewport.w - worldRect.x;
    }
    if (worldRect.y + worldRect.h > viewport.y + viewport.h) {
        worldRect.h = viewport.y + viewport.h - worldRect.y;
    }
    return worldRect;
}