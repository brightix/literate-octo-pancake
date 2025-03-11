#pragma once
#include "../../BehaviorTree/paralle/ParalleNode.h"
#include "../../BehaviorTree/BTNode.h"
#include "../BaseObject.h"
#include "PlayerState.h"

constexpr short player_attrs_count = 4;

enum ObjectAttr {
	player_x,
	player_y,
	player_health,
	player_move_speed,
};

class PlayerObject : public BaseObject{
public:
	PlayerObject();
	std::array<float,4>& getAttrs();
	void setMove(float nx, float ny);
	void update();
	void render();

	ObjectState getBaseState() override;
	PlayerState getState();
	void setPlayerState(PlayerState playerState);
	void removePlayerState(PlayerState playerState);

protected:
	std::array<float, player_attrs_count> attrs;
	std::unique_ptr<ParalleNode> root;
	std::unique_ptr<BTNode> renderNode;
	PlayerState playerState;
};