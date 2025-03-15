#pragma once
#include "pch.h"

enum class ObjectState {
	Idle = 0,
	None = 1 << 0
};

class Rect {
public:
	std::shared_ptr<SDL_FRect> rect;
	Rect() = default;
	Rect(std::shared_ptr<SDL_FRect> rect);
	bool contains(float px, float py) const;
	bool intersects(const Rect& other) const;
};

class BaseObject
{
public:
	virtual SDL_FRect* getRect();
	BaseObject() = default;
	~BaseObject() = default;
	virtual ObjectState getBaseState() = 0;
protected:
	std::shared_ptr<Rect> hitBox;

	SDL_FRect renderRect;
	ObjectState objectState;
};

