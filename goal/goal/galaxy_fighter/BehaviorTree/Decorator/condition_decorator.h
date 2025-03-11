#pragma once
#include "../BTNode.h"
#include "Decorator.h"

class condition_decorator : public Decorator
{
	function<bool(SDL_FRect&)> condition;
	SDL_FRect& rect;
public:
	condition_decorator(unique_ptr<BTNode> child, function<bool(SDL_FRect&)> func, SDL_FRect& rect);
	bool execute() override;
private:
};

