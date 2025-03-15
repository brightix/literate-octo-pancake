#pragma once
#include "../../../BehaviorTree/paralle/ParalleNode.h"
#include "../../camera/Camera.h"
#include "../../../core/Context.h"


class MapObject
{
public:
	MapObject(const nlohmann::json& config);

	void update();

	void render();
	SDL_FRect* getWholeRect();
	SDL_Texture* getTexture();
protected:
	shared_ptr<Context> context;
	void setContext();
	Camera* camera;
	std::unique_ptr<ParalleNode> root;
	shared_ptr<BTNode> renderNode;
};


