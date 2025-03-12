#pragma once
#include "../../BehaviorTree/paralle/ParalleNode.h"
#include "../../BehaviorTree/BTNode.h"
#include "../BaseObject.h"
#include "PlayerState.h"
#include "SpritePlayer.h"

constexpr short player_attrs_count = 9;

enum PlayerAttr {
	player_x,
	player_y,
	player_health,
	player_move_speed,

	player_render_width,
	player_render_height,

	player_sprite_texture_width,
	player_sprite_texture_height,
	player_sprite_frame
};

class PlayerObject : public BaseObject{
public:
	PlayerObject();
	std::array<float,player_attrs_count>& getAttrs();
	void setMove(float nx, float ny);
	void update();
	void render();

	ObjectState getBaseState() override;
	PlayerState getState();
	void setPlayerState(PlayerState playerState);
	void removePlayerState(PlayerState playerState);

	void resetState();

	virtual void refreshAnimationTime();

protected:
	std::array<float, player_attrs_count> attrs;
	std::unique_ptr<ParalleNode> root;
	std::unique_ptr<BTNode> renderNode;
	PlayerState playerState;
	std::unique_ptr<SpritePlayer> sprite;
};