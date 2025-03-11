#include "pch.h"
#include "Player_GreenTofu.h"
#include "../../BehaviorTree/BTAction_player/BTAction_player.h"

Player_GreenTofu::Player_GreenTofu()
{
	this->rect = {1000,1000,100,100};//渲染出来的大小

	texture = ResourceManager::getInstance().get_sprite_sheet_player()[0].get();//获取豆腐的贴图
	this->srcRect = { 0,0,128,128 };
	//renderNode = make_unique<BTAction_player::display_anime_at_center>(texture,&srcRect,&rect,0.0);
	root = make_unique<ParalleNode>();

	root->addChild(make_unique<BTAction_player::player_move_sprite>(*this));
	sprite = SpritePlayer(texture,&rect,playerState, 128, 128, 8);
}

void Player_GreenTofu::update()
{
	root->execute();
}

void Player_GreenTofu::refreshAnimationTime() {

}