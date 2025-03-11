#pragma once
#include "pch.h"

enum class ObjectState {
	Idle = 0,
	None = 1 << 0
};

class BaseObject
{
public:
	SDL_FRect& getRect();
	BaseObject() = default;
	~BaseObject() = default;
	virtual ObjectState getBaseState() = 0;
protected:
	SDL_FRect rect;
	SDL_FRect renderRect;
	ObjectState objectState;
};

