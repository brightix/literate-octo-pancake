#pragma once
#include "pch.h"
#include "../../BehaviorTree/paralle/ParalleNode.h"
#include "playerObject.h"

class PlayerObject;
struct PlayerAttrs;

class SpritePlayer{

	std::shared_ptr<PlayerObject> player;
	std::shared_ptr<SDL_Texture> texture;
	std::shared_ptr<std::vector<float>> actionFrameDelay;
	std::shared_ptr<PlayerAttrs> attrs;
	std::unique_ptr<ParalleNode> root;
	

	std::vector<SDL_FRect> frames;
	std::shared_ptr<SDL_FRect> srcrect, dstrect;
	double angle;
	float elapsed = 0.0;
	short curFrame = 0;
	std::string actionState;
public:
	//≥ı ºªØ
	SpritePlayer(PlayerObject* player);

	bool update();
	void setSpriteFrameRect();
	std::string TransFormState();
	SDL_FRect& getFrame(int idx);
};

