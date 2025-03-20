#include "pch.h"
#include "display_at_position.h"

display_at_position::display_at_position(shared_ptr<SDL_Texture> texture, shared_ptr<SDL_FRect> srcrect, shared_ptr<SDL_FRect> dstrect, double* angle,int* isFacingRight) :
	texture(texture), srcrect(srcrect), dstrect(dstrect), angle(angle) ,isFacingRight(isFacingRight){}

bool display_at_position::execute() {

	if(SDL_RenderTextureRotated(RendererManager::Instance().getRenderer(), texture.get(), srcrect.get(), dstrect.get(), *angle, nullptr, *isFacingRight > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL)) {
		return true;
	}
	else {
		SDL_Log("‰÷»æŒ∆¿Ì ß∞‹");
		return false;
	}
}

