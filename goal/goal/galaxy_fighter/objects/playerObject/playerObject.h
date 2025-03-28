#pragma once
#include "../../BehaviorTree/paralle/ParalleNode.h"
#include "../../BehaviorTree/BTNode.h"
#include "../BaseObject.h"
#include "../../FSM/Player/PlayerState.h"
#include "../../FSM/Player/SubState.h"
#include "../../../json.hpp"
#include "../../core/physics/QuadTree.h"
#include "SpritePlayer.h"
using namespace std;


class SpritePlayer;

typedef struct SpriteSheet {
	int startFrame;//开始帧
	int endFrame;
	float actionDelay;
	bool isLoop;//是否循环播放
	bool isInterruptible;
}SpriteSheet;

typedef struct PlayerAttrs {
	float playerX;
	float playerY;
	float velocityX;
	float velocityY;
	float MaxRunStrength;
	float MaxJumpStrength;

	float gravity;
	float accelerationX;
	float accelerationY;
	float friction;
	float playerHP;
	float player_move_speed;


	float player_render_width;
	float player_render_height;

	float player_sprite_frame_width;
	float player_sprite_frame_height;
	float player_sprite_frame;
	int player_orientation;
}PlayerAttrs;


class PlayerObject : public BaseObject {
public:

	PlayerObject(const nlohmann::json& config);
	void update();
	void render();
	void refreshRenderRect();
	void resetActionState();


	//玩家个人信息
	shared_ptr<PlayerAttrs> getAttrs();
	shared_ptr<SDL_Texture> getTexture();
	unordered_map<string, bool>* getActionState();
	shared_ptr<vector<string>> getActionPriority();
	Rect* getHitBox() override;
	shared_ptr<SDL_FRect> getRenderRect();
	shared_ptr<vector<float>> getActionFrameDelay();
	shared_ptr<unordered_map<std::string,SpriteSheet>> getSpriteSheet();

	float getMaxRunStrength();
	float getPositionX();
	float getVelocityX();
	float getEventVelocityX();
	float getEventVelocityY();
	float getMoveVelocityX();

	float getPositionY();
	float getVelocityY();
	float getAccelerationX();
	float getMoveVelocityY();
	float getAccelerationY();

	int getOrientation();

	float getGravity();

	float getMaxJumpStrength();

	float getFriction();

	float getMaxLightAttackRange();

	string getCurrentStateName();
	PlayerState* getCurrentState();

	nlohmann::json& getConfig();

	void setPositionX(float val);
	void setPositionY(float val);
	void setEventVelocityX(float val);


	void setMoveVelocityX(float val);
	void setMoveVelocityY(float val);

	void addVelocityX(float val);
	void addVelocityY(float val);

	void setOrientation(float val);
	void on_collision(BaseObject* other);




	string printActionState();
	void setHitBox(string action);

	void setReflectHitX(bool val);

	void setReflectHitY(bool val);

	bool IsMovingLeft();
	bool IsMovingRight();
	bool IsMoving();
	bool IsEventVelocityExistX();
	bool IsJumpingOnce();
	bool IsJumping();
	bool IsCrouching();
	bool IsFalling();
	bool IsGrounded();

	bool IsLightAttack();

	bool IsReflectHitX();
	bool IsReflectHitY();
	void ChangeState(PlayerState* newState);

	void ChangeSubState(SubState* newState);

	SDL_FRect* getActionFrameRect();

	void setActionFrameStart();


private:
	nlohmann::json config;

	unordered_map<string,bool> actionState;
	unordered_map<string,float> jumpData;

	shared_ptr<SDL_Texture> texture;

	shared_ptr<SpritePlayer> sprite;
	shared_ptr<ParalleNode> root;
	shared_ptr<Rect> hitBox;
	shared_ptr<SDL_FRect> renderRect;
	shared_ptr<PlayerAttrs> attrs;
	shared_ptr<unordered_map<std::string, SpriteSheet>> spriteSheet;
	shared_ptr<vector<float>> actionFrameDelay;
	shared_ptr<std::vector<string>> actionPriority;

	PlayerState* currentState;
	SubState* subState;

	void loadActionFrame();

	std::vector<SDL_FRect> frames;
	float elapsed = 0;
	int curFrame = 0;

	float attackSuccess = 0;

	bool isReflectHitX;
	float moveVelocityX = 0.0f;
	float eventVelocityX = 0.0f;

	bool isReflectHitY;
	float moveVelocityY = 0.0f;
	float eventVelocityY = 0.0f;
};
























//class PlayerObject : public BaseObject {
//public:
//	PlayerObject(const nlohmann::json& config);
//	bool setBehavior_tree(const nlohmann::json& config, std::function < std::shared_ptr<BTNode>(const nlohmann::json&, std::shared_ptr<Context> ) >nodeFactory);
//	void update();
//	void render();
//
//	void move();
//
//	PlayerAttrs* getAttrs();
//	PlayerState* getState();
//
//	const std::string printState();
//	void setPlayerState(PlayerState playerState);
//	void removePlayerState(PlayerState playerState);
//
//	void resetState();
//
//	SDL_FRect* getRect();
//
//protected:
//
//	PlayerState* playerState;
//	std::unique_ptr<ParalleNode> root;
//	std::unique_ptr<BTNode> renderNode;
//	std::shared_ptr<SpritePlayer> spritePlayer;
//
//
//	std::shared_ptr<Context> context;
//	std::shared_ptr<PlayerAttrs> playerAttrs;
//	std::unordered_map<PlayerState, SpriteSheet> spriteSheet;
//	std::shared_ptr<std::vector<float>> actionFrameDelay;
//
//
//	BlackBoard* bb;
//};