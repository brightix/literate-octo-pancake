#include "pch.h"
#include "BaseObject.h"



Rect::Rect(std::shared_ptr<SDL_FRect> rect) : rect(rect) {}

bool Rect::contains(float px, float py) const
{
	return (px >= rect->x && px <= rect->x + rect->w && py >= rect->y && py <= rect->y + rect->h);
}

bool Rect::intersects(const Rect& other) const {
	return !(
		other.rect->x > rect->x + rect->w ||
		other.rect->x + other.rect->w < rect->x ||
		other.rect->y > rect->y + rect->h ||
		other.rect->y + other.rect->h < rect->y);
}


SDL_FRect* BaseObject::getRect()
{
	if (!hitBox) {
		cerr << "有物体的hitbox为空并且被调用getRect()" << endl;
		return nullptr;
	}
	return hitBox->rect.get();
}


