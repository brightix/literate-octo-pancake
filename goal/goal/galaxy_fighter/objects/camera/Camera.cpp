#include "pch.h"
#include "Camera.h"


Camera& Camera::getInstance() {
	static Camera instance;
	return instance;
}

Camera::Camera() {
	auto [w, h] = Resolution::getInstance().getResolution();
	screen_width = w;
	screen_height = h;
	
	viewport = { 0,0,w,h };
	windowRect = { 0,0,w,h };
}

SDL_FRect* Camera::getViewport() { return &viewport; }

SDL_FRect* Camera::getWindowRect() { return &windowRect; }

void Camera::setCameraOwner(BaseObject* owner) {
	this->owner = owner;
}

void Camera::setCameraRange(SDL_Texture* texture) {
	SDL_GetTextureSize(texture,&world_width,&world_height);
}

pair<float, float> Camera::getCameraRange() { return {world_width, world_height }; }

std::pair<bool, bool>& Camera::ownerxyCrashedState() {
	return isxyCrashed;
}

void Camera::update() {
	SDL_FRect& rect = owner->getRect();
	if (owner->getBaseState() == ObjectState::Idle) return;
	viewport.x = rect.x + rect.w / 2 - windowRect.w / 2;
	viewport.y = rect.y + rect.h / 2 - windowRect.h / 2;

	clampToWorldBounds();
}
void Camera::clampToWorldBounds() {
	auto boundary_x = world_width - viewport.w;
	auto boundary_y = world_height - viewport.h;
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
