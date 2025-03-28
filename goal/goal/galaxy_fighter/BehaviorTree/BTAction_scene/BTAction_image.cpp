#include "pch.h"
#include "BTAction_image.h"
#include "../../utils/Math.h"
#include "../BehaviorRegistry.h"

using namespace BTAction_image;

display_full::display_full(shared_ptr<Context> context){
	Resolution& resolution = Resolution::Instance();
	this->context = context;
	rect = { 0.0f,0.0f,static_cast<float>(resolution.getWindowRect().w),static_cast<float>(resolution.getWindowRect().h) };
}

bool display_full::execute() {
	if (SDL_RenderTexture(RendererManager::Instance().getRenderer(), context->getData<SDL_Texture>("texture").get(), nullptr, &rect)) {
		return true;
	}
	else {
		SDL_Log("渲染纹理失败");
		return false;
	}
}

display_at_position::display_at_position(SDL_Texture* texture, SDL_FRect* rect, double angle) {
	this->texture = texture;
	this->rect = rect;
	this->angle = angle;
}

bool display_at_position::execute() {
	if (SDL_RenderTextureRotated(RendererManager::Instance().getRenderer(), texture, nullptr, rect, angle, nullptr, SDL_FLIP_NONE)) {
		return true;
	}
	else {
		SDL_Log("渲染纹理失败");
		return false;
	}
}


display_background::display_background(shared_ptr<Context> context){
	this->camera = &Camera::Instance();
	this->context = context;
}

bool display_background::execute() {
	if (SDL_RenderTextureRotated(
			RendererManager::Instance().getRenderer(),//渲染器
			context->getData<SDL_Texture>("texture").get(),//纹理
			camera->getViewport(),//相机视野
			&Resolution::Instance().getWindowRect(),
			*context->getData<double>("angle"),//旋转角度
			nullptr,//旋转中心
			SDL_FLIP_NONE//是否翻转
		)) 
	{
		return true;
	}
	else {
		SDL_Log("渲染纹理失败");
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

	elapsed += Timer::Instance().getDeltaAdjustTime() * (isSelecting ? 1 : -1);
	if (elapsed > duration || elapsed < 0) {
		elapsed = clamp(elapsed, 0.0f, (float)duration);
	}
	float t = elapsed / duration;
	curScaleFactor = Math::Lerp(1.0, scaleFactor, t);
	//平滑动画
	float neww = originalSize.w * (1 + (scaleFactor - 1.0f) * Math::SmoothStep(t));
	float newh = originalSize.h * (1 + (scaleFactor - 1.0f) * Math::SmoothStep(t));

	//线性动画
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
	delay_time -= Timer::Instance().getDeltaTime();
	if (delay_time <= 0) {
		return true;
	}
	else return false;
}

check_hover::check_hover(SDL_FRect* rect) {
	this->rect = rect;
}

bool check_hover::execute() {
	if (InputManager::Instance().isCursorHovering(rect)) {
		return true;
	}
	return false;
}


