#include "pch.h"
#include "playerObject.h"
#include "PlayerState.h"
#include "../../BehaviorTree/BTAction_player/BTAction_player.h"
#include "../../BehaviorTree/BTNodeFactory.h"
#include "../../utils/transformUtils.h"
using json = nlohmann::json;

static void from_json(const json& j, PlayerAttrs& p) {
	p.playerX = j.value("playerX", 0.0f);
	p.playerY = j.value("playerY", 0.0f);
	p.playerHP = j.value("playerHP", 5.0f);
	p.player_move_speed = j.value("player_move_speed", 10.0f);
	p.player_render_width = j.value("player_render_width", 128);
	p.player_render_height = j.value("player_render_height", 128);
	p.player_sprite_frame_width = j.value("player_sprite_frame_width", 128.0f);
	p.player_sprite_frame_height = j.value("player_sprite_frame_height", 128.0f);
	p.player_sprite_frame = j.value("player_sprite_frame", 1);
	p.player_orientation = j.value("player_orientation", true);
}

PlayerObject::PlayerObject(const json& config){
	playerAttrs = make_shared<PlayerAttrs>();
	*playerAttrs = config["playerAttrs"].get<PlayerAttrs>();
	playerAttrs->playerX = Resolution::getInstance().getWindowRect().w / 2 - playerAttrs->player_render_width / 2;
	playerAttrs->playerY = Resolution::getInstance().getWindowRect().h / 2 - playerAttrs->player_render_height / 2;
	SDL_FRect trect = {
		playerAttrs->playerX,
		playerAttrs->playerY,
		playerAttrs->player_render_width,
		playerAttrs->player_render_height
	};

	//Rect
	shared_ptr<SDL_FRect> rect = std::make_shared<SDL_FRect>(trect);//渲染出来的大小,设置初始位置
	hitBox = make_shared<Rect>(rect);


	//actionFrameDelay
	vector<float> actionframedelay = {};
	actionFrameDelay = make_shared<std::vector<float>>(actionframedelay);
	for (auto & val : config["actionFrameDelay"]) {
			actionFrameDelay->push_back(val);
	}
	//spriteSheet
	TransformUtils TFUtil;
	for (auto& [key,val] : config["spriteSheet"].items()) {
		if (TFUtil.string2playerState.count(key)) {
			spriteSheet[TFUtil.string2playerState[key]] = {val["startFrame"],val["pre"],val["running"],val["post"],val["endFrame"],val["isLoop"]};
		}
	}

	context = make_shared<Context>();
	context->initData("isPlayerOnGround",make_shared<bool>(false));
	context->initData("playerAttrs",playerAttrs);
	context->initData("interruptible_mask", make_shared<int>(0b00001111));

	context->initData("playerState",make_shared<PlayerState>(PlayerState::Idle));
	playerState = context->getData<PlayerState>("playerState").get();
	context->initData("rect",rect);
	context->initData("spriteSheet", make_shared<std::unordered_map<PlayerState, SpriteSheet>>(spriteSheet));
	context->initData("actionFrameDelay",actionFrameDelay);
	context->initData("texture", ResourceManager::getInstance().getTexture(config["texture"]["catalog"],config["texture"]["fileName"]));
	setBehavior_tree(config["behavior_tree"], createNodeFromJson);
	spritePlayer = make_shared<SpritePlayer>(context);
	context->initData("spritePlayer",spritePlayer);
}

bool PlayerObject::setBehavior_tree(const json& config,function<shared_ptr<BTNode>(const json&,shared_ptr<Context>)> nodeFactory) {
	root = make_unique<ParalleNode>();
	for (auto& node : config["root"]["children"]) {
		root->addChild(nodeFactory(node,context));
	}
	return true;
}

void PlayerObject::update() {
	this->root->execute();
}

void PlayerObject::render()
{
	spritePlayer->update();
}

PlayerAttrs& PlayerObject::getAttrs()
{
	return *context->getData<PlayerAttrs>("playerAttrs").get();
}

ObjectState PlayerObject::getBaseState()
{
	switch (*playerState) {
	case PlayerState::Idle: 
		return ObjectState::Idle;
	default:
		return ObjectState::None;
	}
}

PlayerState PlayerObject::getState()
{
	return *playerState;
}

const std::string PlayerObject::printState() {
	if (!playerState) {
		return "playerState 为空指针";
	}
	switch (*playerState) {
	case PlayerState::Idle:
		return "Idle";
	case PlayerState::Jump:
		return "Jump";
	case PlayerState::Down:
		return "Down";
	case PlayerState::Left:
		return "Left";
	case PlayerState::Right:
		return "Right";
	default:
		return "未知状态";
	}
}

void PlayerObject::setPlayerState(PlayerState playerState)
{
	*this->playerState |= playerState;
}

void PlayerObject::removePlayerState(PlayerState playerState)
{
	*this->playerState |= playerState;
}

void PlayerObject::resetState() {
	*this->playerState = PlayerState::Idle;
}

SDL_FRect* PlayerObject::getRect() {
	return hitBox->rect.get();
}