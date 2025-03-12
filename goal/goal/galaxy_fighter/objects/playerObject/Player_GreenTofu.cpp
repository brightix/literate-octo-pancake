#include "pch.h"
#include "Player_GreenTofu.h"
#include "../../BehaviorTree/BTAction_player/BTAction_player.h"
#include "../../BehaviorTree/BTAction_physics/gravity_heavy.h"
Player_GreenTofu::Player_GreenTofu()
{
	init();
	root = make_unique<ParalleNode>();
	root->addChild(make_unique<BTAction_physics::gravity_heavy>());
	root->addChild(make_unique<BTAction_player::player_move_sprite>(*this));
	sprite = make_unique<SpritePlayer>(texture,&rect,&spriteSheet,&actionFrameDelay,&playerState, attrs[player_sprite_texture_width], attrs[player_sprite_texture_height], attrs[player_sprite_frame]);
}

void Player_GreenTofu::init() {
	attrs = { 0,0,5,4,100,100,128,128,8 };
	auto& res = Resolution::getInstance();

	attrs[player_x] = res.getResolution().first / 2 - attrs[player_render_width] / 2;
	attrs[player_y] = res.getResolution().second / 2 - attrs[player_render_height] / 2;

	texture = ResourceManager::getInstance().get_sprite_sheet_player()[0].get();//获取豆腐的贴图

	rect = { 
		(float)attrs[player_x],
		(float)attrs[player_y],
		attrs[player_render_width],
		attrs[player_render_height]
	};//渲染出来的大小,设置初始位置

	spriteSheet = {
		{PlayerState::Idle,{0,1}},
		{PlayerState::Jump,{0,8}},
		{PlayerState::Left,{0,8}},
		{PlayerState::Down,{0,8}},
		{PlayerState::Right,{0,8}},
	};

	this->actionFrameDelay = {
		{ PlayerState::Idle,100 },
		{ PlayerState::Jump,100 },
		{ PlayerState::Down,100 },
		{ PlayerState::Left,100 },
		{ PlayerState::Right,33 },
		{ PlayerState::Left | PlayerState::Jump,100 },
		{ PlayerState::Right | PlayerState::Jump,100 }
	};
}

void Player_GreenTofu::update()
{
	root->execute();
}
