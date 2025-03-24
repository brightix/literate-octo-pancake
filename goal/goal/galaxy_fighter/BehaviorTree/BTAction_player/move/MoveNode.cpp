#include "pch.h"
#include "MoveNode.h"
MoveNode::MoveNode(PlayerObject* player) : player(player){}
bool MoveNode::execute() {
    shared_ptr<PlayerAttrs> attrs = player->getAttrs();
    auto& input = InputManager::Instance();
    float delta = Timer::Instance().getVelocityFactor();
    auto state = player->getActionState();
    int dx = 0;
    if (input.isKeyPressed(SDL_SCANCODE_A)) {
        dx -= 1;
    }
    if (input.isKeyPressed(SDL_SCANCODE_D)) {
        dx += 1;
    }
    if (dx) {
        //ÓÐÊäÈë
        (*state)["Run"] = true;
        static float MaxRunStrength = 5;

        if (attrs->player_orientation != dx || attrs->velocityX == 0) {
            attrs->velocityX = 0.1f * dx;
            attrs->player_orientation = dx;
        }

        attrs->velocityX *= exp(attrs->accelerationX * delta);
        attrs->velocityX = clamp(attrs->velocityX,-MaxRunStrength,MaxRunStrength);
    }
    else {
        if (attrs->velocityX > 0) {
            attrs->velocityX -= attrs->friction * log(1 + delta);
            if (attrs->velocityX < 0) {
                attrs->velocityX = 0;
            }
        }
        else if (attrs->velocityX < 0) {
            attrs->velocityX += attrs->friction * log(1 + delta);
            if (attrs->velocityX > 0) {
                attrs->velocityX = 0;
            }
        }
        else {
            attrs->velocityX = 0;
        }
        (*state)["Run"] = false;
    }
    attrs->playerX += attrs->velocityX;
    return false;
}

