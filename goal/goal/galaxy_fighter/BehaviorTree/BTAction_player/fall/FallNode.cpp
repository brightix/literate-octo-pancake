#include "pch.h"
#include "FallNode.h"

FallNode::FallNode(PlayerObject* player) : player(player)
{
}

bool FallNode::execute()
{
	PlayerAttrs* attrs = player->getAttrs().get();
	float delta = Timer::Instance().getVelocityFactor();
	auto state = player->getActionState();
	auto& input = InputManager::Instance();
	if (!(*state)["OnGround"] && !(*state)["Jump"]) {
		if (!(*state)["Fall"]) {
			(*state)["Fall"] = true;
			attrs->velocityY = 0;
		}
		else {
			attrs->velocityY += attrs->gravity * delta;
			attrs->velocityY = min(attrs->velocityY,500*delta);
		}
		attrs->playerY += attrs->velocityY * delta;
	}
	else {
		(*state)["Fall"] = false;
	}
	return false;
}
