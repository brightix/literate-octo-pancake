#pragma once
#include "../../BehaviorTree/paralle/ParalleNode.h"
#include "../../BehaviorTree/BTNode.h"
#include "../BaseObject.h"
#include "PlayerState.h"
#include "SpritePlayer.h"
#include "../../../json.hpp"

typedef struct PlayerAttrs {
	float playerX;
	float playerY;
	float playerHP;
	float player_move_speed;


	float player_render_width;
	float player_render_height;

	float player_sprite_frame_width;
	float player_sprite_frame_height;
	float player_sprite_frame;
	bool player_orientation;
}PlayerAttrs;

class PlayerObject : public BaseObject {
public:
	PlayerObject(const nlohmann::json& config);
	bool setBehavior_tree(const nlohmann::json& config, std::function < std::shared_ptr<BTNode>(const nlohmann::json&, std::shared_ptr<Context> ) >nodeFactory);
	void update();
	void render();

	PlayerAttrs& getAttrs();

	ObjectState getBaseState() override;
	PlayerState getState();

	const std::string printState();
	void setPlayerState(PlayerState playerState);
	void removePlayerState(PlayerState playerState);

	void resetState();

protected:
	PlayerState* playerState;
	std::unique_ptr<ParalleNode> root;
	std::unique_ptr<BTNode> renderNode;
	std::unique_ptr<SpritePlayer> sprite;

	std::shared_ptr<Context> context;
	std::shared_ptr<PlayerAttrs> playerAttrs;
	std::unordered_map<PlayerState, SpriteSheet> spriteSheet;
	std::unordered_map<PlayerState, double> actionFrameDelay;
};