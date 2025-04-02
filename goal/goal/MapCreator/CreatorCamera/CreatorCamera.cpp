#include "pch.h"
#include "CreatorCamera.h"

CreatorCamera::CreatorCamera(SDL_FRect viewport) : viewport(viewport) {}

void CreatorCamera::setViewportXY(float x,float y) {
    if (world) {
        viewport.x = clamp(x,world->x,world->x + world->w - viewport.w);
        viewport.y = clamp(y, world->y, world->y + world->h - viewport.h);
    }
    else {
        viewport.x = x;
        viewport.y = y;
    }
}

void CreatorCamera::setViewportWH(float w, float h) {
    if (world) {
        viewport.w = clamp(w, world->w, world->w + world->w - viewport.w);
        viewport.h = clamp(h, world->h, world->h + world->h - viewport.h);
    }
    else {
        viewport.w = w;
        viewport.h = h;
    }
}


void CreatorCamera::addViewportXY(float x, float y) {
    if (world) {
        viewport.x = clamp(viewport.x + x, world->x, world->x + world->w - viewport.w);
        viewport.y = clamp(viewport.y + y, world->y, world->y + world->h - viewport.h);
    }
    else {
        viewport.x += x;
        viewport.y += y;
    }
}
void CreatorCamera::addViewportWH(float w, float h) {
    if (world) {
        viewport.w = clamp(viewport.w + w, world->w, world->w + world->w - viewport.w);
        viewport.h = clamp(viewport.w + h, world->h, world->h + world->h - viewport.h);
    }
    else {
        viewport.w += w;
        viewport.h += h;
    }
}


const SDL_FRect& CreatorCamera::GetViewport() { return viewport; }

void CreatorCamera::setCameraRange(SDL_FRect* Area) {
	world = Area;
}

const SDL_FRect& CreatorCamera::getCameraRange() { return *world; }


bool CreatorCamera::isOnScreen(SDL_FRect& worldRect) {
    return !(
        worldRect.x + worldRect.w < viewport.x ||
        worldRect.x > viewport.x + viewport.w ||
        worldRect.y + worldRect.h < viewport.y ||
        worldRect.y > viewport.y + viewport.h
    );
}



//rect.x, rect.y, rect.w, rect.h

/**
 * @brief 将世界坐标转换为 UI 显示坐标
 *
 * 这个函数基于 `viewport` 的缩放比例，将 `rect` 由世界坐标转换为 `windowShowRect` 内的相对坐标。
 *
 * \param windowShowRect  UI 窗口的显示区域
 * \param rect            世界坐标中的矩形
 * @return SDL_FRect      转换后的 UI 矩形坐标
 */
SDL_FRect CreatorCamera::WorldToViewport_rect(SDL_FRect& windowShowRect, SDL_FRect rect) {
    float scaleX = windowShowRect.w / viewport.w;
    float scaleY = windowShowRect.h / viewport.h;

    return {
        windowShowRect.x + (rect.x - viewport.x) * scaleX,
        windowShowRect.y + (rect.y - viewport.y) * scaleY,
        rect.w * scaleX,
        rect.h * scaleY
    };
}

SDL_FRect CreatorCamera::WorldToViewport_line(SDL_FRect& showRect, SDL_FRect line) {
	return {	
		line.x - viewport.x + showRect.x,
		line.y - viewport.y + showRect.y,
		line.w - viewport.x + showRect.x,
		line.h - viewport.y + showRect.y };
}

SDL_FPoint CreatorCamera::WorldToViewport_dot(SDL_FRect& showRect, SDL_FPoint worldPos) {
	return { 
		showRect.x + (worldPos.x - viewport.x) * (showRect.w / viewport.w),
		showRect.y + (worldPos.y - viewport.y) * (showRect.h / viewport.h) };
}

//显示坐标转换为内部世界坐标
SDL_FRect CreatorCamera::ScreenToWorld_rect(SDL_FRect& dstRect, SDL_FRect rect) {
    return {
        dstRect.x + (rect.x - viewport.x) * (dstRect.w / viewport.w),
        dstRect.y + (rect.y - viewport.y) * (dstRect.h / viewport.h),
        rect.w * (dstRect.w / viewport.w),
        rect.h * (dstRect.h / viewport.h)
    };
}

SDL_FPoint CreatorCamera::ScreenToWorld_dot(SDL_FRect& dstRect, SDL_FPoint screenP) {
    return {
        (screenP.x - dstRect.x) * (viewport.w / dstRect.w) + viewport.x,
        (screenP.y - dstRect.y) * (viewport.h / dstRect.h) + viewport.y
    };
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


