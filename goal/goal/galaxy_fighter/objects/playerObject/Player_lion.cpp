#include "pch.h"
#include "Player_lion.h"
#include "../../BehaviorTree/BTAction_player/BTAction_player.h"
using namespace BTAction_player;

Player_lion::Player_lion() {
	texture = ResourceManager::getInstance().get_hero()[1].get();
	
	renderNode = make_unique<display_at_center>(texture,&rect,0.0);
	
	
	root = make_unique<ParalleNode>();
	root->addChild(make_unique<player_move_image>(*this));
	//root->addChild(make_unique<display_at_center>(texture, &rect,0.0));
}

void Player_lion::update()
{
}
