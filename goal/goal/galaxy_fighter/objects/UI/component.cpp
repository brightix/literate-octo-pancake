#include "pch.h"
#include "component.h"

SDL_FRect* component::getRect() {
	return renderRect.get();
}
