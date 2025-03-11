#include "pch.h"
#include "condition_decorator.h"

condition_decorator::condition_decorator(unique_ptr<BTNode> child, function<bool(SDL_FRect&)> func, SDL_FRect& rect) : Decorator(move(child)),rect(rect) {
	this->condition = func;
}

bool condition_decorator::execute() {
	if (!condition(rect)) {
		return child->execute();
	}
	return false;
}