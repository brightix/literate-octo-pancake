#include "pch.h"
#include "Player_GreenTofu.h"
#include "../../BehaviorTree/BTAction_player/BTAction_player.h"

Player_GreenTofu::Player_GreenTofu()
{
	texture = ResourceManager::getInstance().get_hero()[0].get();

	renderNode = make_unique<BTAction_player::display_anime_at_center>(texture,&srcRect,&rect,0.0);
	root = make_unique<ParalleNode>();
	root->addChild(make_unique<BTAction_player::player_move_sprite>(*this));
	root->addChild(make_unique<BTAction_player::cal_sprite_rect>());
}

void Player_GreenTofu::update()
{

}
