#include "pch.h"
#include "playerObject.h"
#include "PlayerState.h"
#include "../../BehaviorTree/BTAction_player/BTAction_player.h"

PlayerObject::PlayerObject(){
	auto& res = Resolution::getInstance();
	rect = { (float)res.getResolution().first / 2,(float)res.getResolution().second / 2,100,100};
	attrs[player_x] = rect.x;
	attrs[player_y] = rect.y;
	attrs[player_health] = 5;
	attrs[player_move_speed] = 10;
}

std::array<float,player_attrs_count>& PlayerObject::getAttrs() { return attrs; }

void PlayerObject::setMove(float nx,float ny) {
	rect.x = nx;
	rect.y = ny;
}

void PlayerObject::update() {
	this->root->execute();
}

void PlayerObject::render()
{
	sprite->update();
}

ObjectState PlayerObject::getBaseState()
{
	switch (playerState) {
	case PlayerState::Idle: 
		return ObjectState::Idle;
	default:
		return ObjectState::None;
	}
}

PlayerState PlayerObject::getState()
{
	return playerState;
}

void PlayerObject::setPlayerState(PlayerState playerState)
{
	this->playerState |= playerState;
}

void PlayerObject::removePlayerState(PlayerState playerState)
{
	this->playerState |= playerState;
}

void PlayerObject::resetState() {
	this->playerState = PlayerState::Idle;
}

void PlayerObject::refreshAnimationTime() {

}