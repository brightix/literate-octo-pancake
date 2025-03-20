#include "pch.h"
#include "JumpNode.h"

JumpNode::JumpNode(PlayerObject* player)
{
	this->player = player;
}

bool JumpNode::execute()
{
    auto& input = InputManager::Instance();
    auto attrs = player->getAttrs();
	float delta = Timer::Instance().getVelocityFactor();
	static float MaxJumpStrength = 15;
	static float accelerationY = 0.45;
	auto state = player->getActionState();
    if (input.isKeyPressed(SDL_SCANCODE_W) && !(*state)["isFall"]) {
        if ((*state)["isOnGround"] && input.isKeyPressedOnce(SDL_SCANCODE_W)) {
			attrs->velocityY = -MaxJumpStrength;
			(*state)["isJump"] = true;
		}
		else {
			attrs->velocityY += accelerationY * delta;
			if (attrs->velocityY >= 0) {
				attrs->velocityY = 0;
				(*state)["isJump"] = false;
			}
		}
		attrs->playerY += attrs->velocityY * delta;
    }
	else {
		(*state)["isJump"] = false;
	}
    return false;
}
