#include "pch.h"
#include "MapObject.h"
#include "../../../BehaviorTree/BTAction_scene/BTAction_image.h"
#include "../../../BehaviorTree/BTNodeFactory.h"
#include "../../camera/Camera.h"

using json = nlohmann::json;

MapObject::MapObject(const json& config){
	
	this->camera = &Camera::Instance();
	this->context = make_shared<Context>();
	std::string catalog = config["texture"]["catalog"];
	std::string fileName = config["texture"]["fileName"];
	context->initData("texture", ResourceManager::Instance().getTexture(catalog,fileName));


	shared_ptr<double> angle = make_shared<double>(config["texture"]["angle"].get<double>());
	context->initData("angle",angle);

	//初始化地图矩形
	float resScale = Resolution::Instance().getScaleFactor();
	auto texture = context->getData<SDL_Texture>("texture").get();
	SDL_FRect wholeRect = { 0,0,0,0};
	SDL_GetTextureSize(texture, &wholeRect.w, &wholeRect.h);
	wholeRect.x *= resScale;
	wholeRect.y *= resScale;
	wholeRect.w *= resScale;
	wholeRect.h *= resScale;
	context->initData("wholeRect",make_shared<SDL_FRect>(wholeRect));

	root = make_unique<ParalleNode>();
	for (auto& node : config["behavior_tree"]["renderNode"]["children"]) {
		std::string nodeName = node["name"];
		if (nodeName == "display_background") {
			renderNode = createNodeFromJson(node,context);
		}
	}
}

void MapObject::setContext() {

}


void MapObject::update()
{
	root->execute();
}

void MapObject::render()
{
	renderNode->execute();
}

SDL_FRect* MapObject::getWholeRect()
{
	return context->getData<SDL_FRect>("wholeRect").get();
}

SDL_Texture* MapObject::getTexture()
{
	return context->getData<SDL_Texture>("texture").get();
}

