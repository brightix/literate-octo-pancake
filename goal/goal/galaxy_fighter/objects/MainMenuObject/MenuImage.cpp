#include "pch.h"
#include "MenuImage.h"
#include "../../BehaviorTree/BTAction_scene/BTAction_image.h"

using namespace BTAction_image;
MenuButton::MenuButton(SDL_Texture* texture,float scale, float x, float y) {
	float f = Resolution::getInstance().getScaleFactor();
	
	this->texture = texture;
	this->renderer = RendererManager::getInstance().getRenderer();
	this->rect = { x,y, 0.0f,0.0f };
	SDL_GetTextureSize(texture,&rect.w,&rect.h);
	this->rect.w *= f*scale;
	this->rect.h *= f*scale;
	root = make_unique<ParalleNode>();
	root->addChild(move(make_unique<scaling_up_hovering>(rect,1.5f,200.0f,isSelecting)));
	root->addChild(move(make_unique<display_at_position>(texture,&rect,0.0f)));
}

SDL_FRect& MenuButton::getRect() { return rect; }

void MenuButton::update() {
	isSelecting = InputManager::getInstance().isCursorHovering(rect);
	root->execute();
}


MenuBackground::MenuBackground(SDL_Texture* texture) {
	this->texture = texture;
	root = make_unique<ParalleNode>();
	root->addChild(make_unique<display_full>(texture));
}

void MenuBackground::update() {
	root->execute();
}
