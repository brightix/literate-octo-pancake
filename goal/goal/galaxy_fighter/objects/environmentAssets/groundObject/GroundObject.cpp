#include "pch.h"
#include "GroundObject.h"
#include "../../../core/resourceManager.h"

GroundObject::GroundObject(float x, float y, float scaleFactor) : BaseObject(ObjectType::Ground)
{
	float resFactor = Resolution::Instance().getScaleFactor();
	SDL_FRect trect = { x * resFactor,y * resFactor,100,100 };
	texture = ResourceManager::Instance().getTexture("bk","bk_3.jpg");
	SDL_GetTextureSize(texture.get(), &trect.w,&trect.h);
	trect.w *= scaleFactor;
	trect.h *= scaleFactor;
	hitBox = make_shared<Rect>(Rect(trect));
	worldRect = make_shared<SDL_FRect>(trect);
}

void GroundObject::update(){}

void GroundObject::render()
{
	auto renderer = RendererManager::Instance().getRenderer();
	auto& camera = Camera::Instance();
	if (camera.isOnScreen(*worldRect)) {
		auto showRect = camera.worldToScreen(*worldRect);
		SDL_RenderTexture(renderer,texture.get(),nullptr, &showRect);
		SDL_RenderRect(renderer, &showRect);
	}


}

Rect* GroundObject::getHitBox() {
	return hitBox.get();
}

void GroundObject::on_collision(BaseObject* other) {
	return;
}
