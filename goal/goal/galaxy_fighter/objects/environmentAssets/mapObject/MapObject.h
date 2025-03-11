#pragma once
#include "../../../BehaviorTree/paralle/ParalleNode.h"
#include "../../camera/Camera.h"

class MapObject
{
public:
	MapObject(SDL_Texture* texture);
	void update();

	void render();

	SDL_Texture* getTexture();
protected:
	SDL_Texture* texture;
	Camera* camera;
	std::unique_ptr<ParalleNode> root;
	unique_ptr<BTNode> renderNode;
};




class test_bk : public MapObject {
public:
	test_bk(SDL_Texture* texture);

};

