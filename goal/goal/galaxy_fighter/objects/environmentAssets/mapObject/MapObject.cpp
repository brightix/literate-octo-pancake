#include "pch.h"
#include "MapObject.h"
#include "../../../BehaviorTree/BTAction_image.h"
#include "../../camera/Camera.h"

MapObject::MapObject(SDL_Texture* texture){
	this->texture = texture;
	this->camera = &Camera::getInstance();

	root = make_unique<ParalleNode>();
	renderNode = std::make_unique<BTAction_image::display_background>(texture,0.0);
}


void MapObject::update()
{
	root->execute();
}

void MapObject::render()
{
	renderNode->execute();
}

SDL_Texture* MapObject::getTexture()
{
	return texture;
}

test_bk::test_bk(SDL_Texture* texture) :MapObject(texture){}

