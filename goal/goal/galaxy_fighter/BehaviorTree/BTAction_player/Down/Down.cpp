#include "pch.h"
#include "Down.h"

DownNode::DownNode(PlayerObject* player)
{
	this->player = player;
}

bool DownNode::execute()
{
	auto& input = InputManager::Instance();
	auto attrs = player->getAttrs();
	float delta = Timer::Instance().getVelocityFactor();
	auto state = player->getActionState();
	if (input.isKeyPressed(SDL_SCANCODE_S) && (*state)["OnGround"]) {
		if (input.isKeyPressedOnce(SDL_SCANCODE_S)) {
			(*state)["Idle_to_Down"] = true;
			(*state)["Down"] = true;
			//player->setHitBox("Crouching");
		}
		return true;
	}
	else {
		if ((*state)["Down"]) {
			(*state)["Down"] = false;
			(*state)["Down_to_Idle"] = true;
			//player->setHitBox("StandingUp");
		}
	}
	return false;
}


