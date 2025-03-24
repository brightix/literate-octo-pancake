#include "pch.h"
#include "Camera.h"


Camera& Camera::Instance() {
	static Camera instance;
	return instance;
}

Camera::Camera() {
	this->owner = nullptr;

	windowRect = Resolution::Instance().getWindowRect();
	viewport = windowRect;
	world = &windowRect;
}

void Camera::setViewport(SDL_FRect curWindowRect) {
	viewport = curWindowRect;
}

SDL_FRect* Camera::getViewport() { return &viewport; }

void Camera::setCameraOwner(BaseObject* owner) {
	this->owner = owner;
	clampToWorldBounds();
}

void Camera::setCameraRange(SDL_FRect* map) {
	world = map;
}

SDL_FRect& Camera::getCameraRange() { return *world; }

std::pair<bool, bool>& Camera::ownerxyCrashedState() {
	return isxyCrashed;
}

void Camera::update() {
	SDL_FRect& rect = owner->getHitBox()->rect;
	//if (!rect) {
	//	throw "相机持有者的hitbox为nullptr";
	//}
	viewport.x = rect.x + rect.w / 2 - windowRect.w / 2;
	viewport.y = rect.y + rect.h / 2 - windowRect.h / 2;
	clampToWorldBounds();
}
void Camera::clampToWorldBounds() {
	auto boundary_x = max(0.0f,world->w - viewport.w);
	auto boundary_y = max(0.0f,world->h - viewport.h);
	isxyCrashed = {false, false};
	if (viewport.x < 0) {
		viewport.x = 0;
		isxyCrashed.first = true;
	}
	else if (viewport.x > boundary_x) {
		viewport.x = boundary_x;
		isxyCrashed.first = true;
	}
	if (viewport.y < 0) {
		viewport.y = 0;
		isxyCrashed.second = true;
	}
	else if (viewport.y > boundary_y) {
		viewport.y = boundary_y;
		isxyCrashed.second = true;
	}
}

bool Camera::isOnScreen(SDL_FRect& rect) {
	return !(rect.x + rect.w < viewport.x || rect.x > viewport.x + viewport.w ||
		rect.y + rect.h < viewport.y || rect.y > viewport.y + viewport.h);
}

SDL_FRect Camera::worldToScreen(SDL_FRect& rect) {
	return { rect.x - viewport.x,rect.y - viewport.y,rect.w,rect.h };
}