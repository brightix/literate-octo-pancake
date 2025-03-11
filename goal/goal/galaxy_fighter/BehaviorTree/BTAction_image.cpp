#include "pch.h"
#include "BTAction_image.h"
#include "utils/BTMath.h"
#include "BehaviorRegistry.h"

using namespace BTAction_image;

display_full::display_full(SDL_Texture* texture) {
	Resolution& resolution = Resolution::getInstance();
	this->texture = texture;
	rect = { 0.0f,0.0f,static_cast<float>(resolution.getResolution().first),static_cast<float>(resolution.getResolution().second) };
}

bool display_full::execute() {
	if (SDL_RenderTexture(RendererManager::getInstance().getRenderer(), texture, nullptr, &rect)) {
		return true;
	}
	else {
		SDL_Log("äÖÈ¾ÎÆÀíÊ§°Ü");
		return false;
	}
}

display_scroll_virtically::display_scroll_virtically(SDL_Texture* texture, SDL_Rect* rect) {
	this->texture = texture;
	this->rect1;
}

bool display_scroll_virtically::execute() {
	//SDL_RenderTexture(RendererManager::getInstance().getRenderer(), texture, nullptr, rect);
	return true;
}

display_at_position::display_at_position(SDL_Texture* texture, SDL_FRect* rect, double angle) {
	this->texture = texture;
	this->rect = rect;
	this->angle = angle;
}

bool display_at_position::execute() {
	if (SDL_RenderTextureRotated(RendererManager::getInstance().getRenderer(), texture, nullptr, rect, angle, nullptr, SDL_FLIP_NONE)) {
		return true;
	}
	else {
		SDL_Log("äÖÈ¾ÎÆÀíÊ§°Ü");
		return false;
	}
}


display_background::display_background(SDL_Texture* texture, double angle)
{
	this->texture = texture;
	this->camera = &Camera::getInstance();
	this->angle = angle;
}

bool display_background::execute() {
	auto showRect = camera->getViewport();
	if (SDL_RenderTextureRotated(RendererManager::getInstance().getRenderer(), texture,showRect, camera->getWindowRect(), angle, nullptr, SDL_FLIP_NONE)) {
		return true;
	}
	else {
		SDL_Log("äÖÈ¾ÎÆÀíÊ§°Ü");
		return false;
	}
}


scaling_up_hovering::scaling_up_hovering(SDL_FRect& rect, float scaleFactor, float duration, bool& isSelecting) : rect(rect), isSelecting(isSelecting) {
	this->originalSize = rect;
	this->scaleFactor = scaleFactor;
	this->duration = duration;
	this->elapsed = 0.0f;
	curScaleFactor = 1.0;
}

bool scaling_up_hovering::execute() {
	if ((!isSelecting && curScaleFactor == 1.0) || (isSelecting && curScaleFactor == scaleFactor)) {
		return false;
	}

	elapsed += Timer::getInstance().getDeltaAdjustTime() * (isSelecting ? 1 : -1);
	if (elapsed > duration || elapsed < 0) {
		elapsed = clamp(elapsed, 0.0f, (float)duration);
	}
	float t = elapsed / duration;
	curScaleFactor = BTMath::Lerp(1.0, scaleFactor, t);
	//Æ½»¬¶¯»­
	float neww = originalSize.w * (1 + (scaleFactor - 1.0f) * BTMath::SmoothStep(t));
	float newh = originalSize.h * (1 + (scaleFactor - 1.0f) * BTMath::SmoothStep(t));

	//ÏßÐÔ¶¯»­
	//float neww = originalSize.w * curScaleFactor;
	//float newh = originalSize.h * curScaleFactor;

	rect.w = neww;
	rect.h = newh;
	rect.x = originalSize.x - (neww - originalSize.w) / 2;
	rect.y = originalSize.y - (newh - originalSize.h) / 2;

	return true;
}

delay::delay(double delay_time)
{
	this->delay_time = delay_time;
}

bool delay::execute()
{
	delay_time -= Timer::getInstance().getDeltaTime();
	if (delay_time <= 0) {
		return true;
	}
	else return false;
}

check_hover::check_hover(SDL_FRect* rect) {
	this->rect = rect;
}

bool check_hover::execute() {
	if (InputManager::getInstance().isCursorHovering(*rect)) {
		return true;
	}
	return false;
}


