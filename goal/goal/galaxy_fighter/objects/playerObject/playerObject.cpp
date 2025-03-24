#include "pch.h"
#include "../../BehaviorTree/BTAction_player/BTAction_player.h"
#include "../../BehaviorTree/BTNodeFactory.h"
#include "../../utils/transformUtils.h"
#include "../../BehaviorTree/BTAction_player/Action.h"

using json = nlohmann::json;

static void from_json(const json& j, PlayerAttrs& p) {
	p.playerX = j.value("playerX", 0.0f);
	p.playerY = j.value("playerY", 0.0f);
	p.velocityX = j.value("velocityX", 0.0f);
	p.velocityY = j.value("velocityY", 0.0f);
	p.MaxRunStrength = j.value("MaxRunStrength", 5.0f);
	p.MaxJumpStrength = j.value("MaxJumpStrength", 10.0f);
	p.gravity = j.value("gravity", 0.4f);
	p.accelerationX = j.value("accelerationX",1.0f);
	p.accelerationY = j.value("accelerationY", 1.0f);
	p.friction = j.value("friction", 1.0f);
	p.playerHP = j.value("playerHP", 5.0f);
	p.player_move_speed = j.value("player_move_speed", 10.0f);
	p.player_render_width = j.value("player_render_width", 128);
	p.player_render_height = j.value("player_render_height", 128);
	p.player_sprite_frame_width = j.value("player_sprite_frame_width", 128.0f);
	p.player_sprite_frame_height = j.value("player_sprite_frame_height", 128.0f);
	p.player_sprite_frame = j.value("player_sprite_frame", 1);
	p.player_orientation = j.value("player_orientation", 1);
}

PlayerObject::PlayerObject(const json& config) : BaseObject(ObjectType::Player){
	ResourceManager& resource = ResourceManager::Instance();
	attrs = make_shared<PlayerAttrs>();
	*attrs = config["playerAttrs"].get<PlayerAttrs>();
	SDL_FRect trect = {
		attrs->playerX,
		attrs->playerY,
		attrs->player_render_width,
		attrs->player_render_height
	};
	texture = resource.getTexture(config["texture"]["catalog"], config["texture"]["fileName"]);
	renderRect = make_shared<SDL_FRect>(trect);
	hitBox = make_shared<Rect>(Rect(trect));

	root = make_shared<ParalleNode>();
	root->addChild(make_shared<FallNode>(this));
	root->addChild(make_shared<MoveNode>(this));

	shared_ptr<Selector> selector = make_shared<Selector>();
	selector->addChild(make_shared<JumpNode>(this));
	selector->addChild(make_shared<DownNode>(this));
	root->addChild(selector);


	actionState = {
		{"isAttack",false},
		{"Idle_to_Jump",false},
		{"Jump",false},
		{"Jump_to_Fall",false},
		{"Fall",false},
		{"Fall_to_Idle",false},
		{"Idle_to_Down",false},
		{"Down",false},
		{"Down_to_Idle",false},
		{"Idle_to_Run",false},
		{"Run",false},
		{"Run_to_Idle",false},
		{"wink",false},
		{"OnGround",false},
	};
	//spriteSheet
	spriteSheet = make_shared<unordered_map<string,SpriteSheet>>();
	actionPriority = make_shared<vector<string>>();
	for (auto& [key,val] : config["spriteSheet"].items()) {
		(*spriteSheet)[key] = { val["startFrame"],val["endFrame"],val["actionDelay"],val["isLoop"],val["isInterruptible"]};
	}
	//actionFrameDelay
	vector<float> actionframedelay = {};
	actionFrameDelay = make_shared<std::vector<float>>(actionframedelay);
	//for (auto & val : config["actionFrameDelay"]) {
	//	actionFrameDelay->push_back(val);
	//}
	sprite = make_shared<SpritePlayer>(this);
	currentState = new IdleState;
	loadActionFrame();
}

void PlayerObject::update() {
	//this->root->execute();
	currentState->Update(*this);
	//if (!IsGrounded()) {
	//	attrs->playerY += 10;
	//}
	float delta = Timer::Instance().getDeltaAdjustTime();
	this->attrs->playerX += attrs->velocityX * delta;
	this->attrs->playerY += attrs->velocityY * delta;
	this->hitBox->rect.x = attrs->playerX;
	this->hitBox->rect.y = attrs->playerY;
}

void PlayerObject::render()
{
	//sprite->update();
	currentState->Render(*this);
}

void PlayerObject::refreshRenderRect() {
	auto& camera = Camera::Instance();
	this->renderRect->x = attrs->playerX;
	this->renderRect->y = attrs->playerY;
	if (camera.isOnScreen(*renderRect)) {
		*renderRect = camera.worldToScreen(*renderRect);
	}
}

void PlayerObject::resetActionState() {
	actionState["OnGround"] = false;
}



shared_ptr<PlayerAttrs> PlayerObject::getAttrs() { return attrs; }

shared_ptr<SDL_Texture> PlayerObject::getTexture() { return texture; }

unordered_map<string,bool>* PlayerObject::getActionState(){ return &actionState;}

shared_ptr<vector<string>> PlayerObject::getActionPriority() { return actionPriority; }

Rect* PlayerObject::getHitBox() { return hitBox.get(); }

shared_ptr<SDL_FRect> PlayerObject::getRenderRect() {
	auto& camera = Camera::Instance();
	if (camera.isOnScreen(*renderRect)) {
		SDL_FRect rectInCamera = camera.worldToScreen(*renderRect);
		
	}
	return renderRect;
}

shared_ptr<vector<float>> PlayerObject::getActionFrameDelay() { return actionFrameDelay; }

shared_ptr<unordered_map<std::string, SpriteSheet>> PlayerObject::getSpriteSheet() { return spriteSheet; }


void PlayerObject::on_collision(BaseObject* other) {

	switch (other->getObjectType()) {
	case Ground:
		Rect* otherHitBox = other->getHitBox();
		if (!otherHitBox) {
			cout << "�������ײ�ĵ�����ײ��Ϊ��,ID :" << other->getObjectType() << endl;
			return;
		}
		SDL_FRect ground = otherHitBox->rect;
		SDL_FRect& rect = hitBox->rect;
		// ������Ҿ��εı߽�
		float playerLeft = rect.x;
		float playerRight = rect.x + rect.w;
		float playerTop = rect.y;
		float playerBottom = rect.y + rect.h;

		// ���������εı߽�
		float groundLeft = ground.x;
		float groundRight = ground.x + ground.w;
		float groundTop = ground.y;
		float groundBottom = ground.y + ground.h;

		float overlapX = min(playerRight - groundLeft, groundRight - playerLeft);
		float overlapY = min(playerBottom - groundTop, groundBottom - playerTop);
		if (overlapY >= 0 && overlapX >= 0) {
			if (overlapX < overlapY) {
				// ˮƽ��ײ
				if (playerRight - groundLeft < groundRight - playerLeft) {
					// ��Ҵ��Ҳ���ײ����
					attrs->playerX = groundLeft - rect.w;
				}
				else {
					// ��Ҵ������ײ����
					attrs->playerX = groundRight;
				}
				attrs->velocityX = 0; // ˮƽ�ٶȹ���
			}
			else {
				// ��ֱ��ײ
				if (playerBottom - groundTop < groundBottom - playerTop) {
					// ��Ҵ��·���ײ����
					attrs->playerY = groundTop - rect.h;
					actionState["OnGround"] = true;
				}
				else {
					// ��Ҵ��Ϸ���ײ����
					attrs->playerY = groundBottom;
				}
				attrs->velocityY = 0; // ��ֱ�ٶȹ���
			}
		}
	}
}

string PlayerObject::printActionState() {
	string res;
	for (auto& [key, val] : actionState) {
		if (val) {
			res += key + "+";
		}
	}
	if (!res.empty()) res.erase(res.end() - 1);
	return res;
}

void PlayerObject::setHitBox(string action) {
	if (action == "Crouching") {
		hitBox->rect.h *= 0.5;
		hitBox->rect.y += hitBox->rect.h;
	}
	else if (action == "StandingUp") {
		hitBox->rect.y -= hitBox->rect.h;
		hitBox->rect.h /= 0.5;
	}
	else {
		cout << "���setHitBox����,δ֪��Ϊ��" << action << endl;
	}
}

//��ȡ�������
float PlayerObject::getPositionX() { return attrs->playerX; }
float PlayerObject::getPositionY() { return attrs->playerY; }


float PlayerObject::getVelocityX() { return attrs->velocityX; }
float PlayerObject::getVelocityY() { return attrs->velocityY; }
float PlayerObject::getAccelerationX() { return attrs->accelerationX; }
float PlayerObject::getAccelerationY() { return attrs->accelerationY; }

int PlayerObject::getOrientation() { return attrs->player_orientation; }
float PlayerObject::getGravity() { return attrs->gravity; }
float PlayerObject::getMaxRunStrength() { return attrs->MaxRunStrength; }
float PlayerObject::getMaxJumpStrength() { return attrs->MaxJumpStrength; }
float PlayerObject::getFriction() { return attrs->friction; }
float PlayerObject::getMaxLightAttackRange() { return 100; }

//������ݼ���
void PlayerObject::setVelocityX(float val) { attrs->velocityX = val; }
void PlayerObject::setVelocityY(float val) { attrs->velocityY = val; }
void PlayerObject::setOrientation(float val) { attrs->player_orientation = val; }

//�������
bool PlayerObject::IsMovingLeft() { return InputManager::Instance().isKeyPressed(SDL_SCANCODE_A); }
bool PlayerObject::IsMovingRight() { return InputManager::Instance().isKeyPressed(SDL_SCANCODE_D); }
bool PlayerObject::IsMoving() { return InputManager::Instance().isKeyPressed(SDL_SCANCODE_A) || InputManager::Instance().isKeyPressed(SDL_SCANCODE_D); }
bool PlayerObject::IsJumping() { return InputManager::Instance().isKeyPressed(SDL_SCANCODE_W); }
bool PlayerObject::IsCrouching() { return InputManager::Instance().isKeyPressed(SDL_SCANCODE_S); }
bool PlayerObject::IsFalling() { return false; }
bool PlayerObject::IsGrounded() { return actionState["OnGround"]; }
bool PlayerObject::IsLightAttack() { return InputManager::Instance().isKeyPressed(SDL_SCANCODE_J); }


//���״̬�л�
void PlayerObject::ChangeState(PlayerState* newState) {
	currentState->Exit(*this);
	delete currentState;
	currentState = newState;
	currentState->Enter(*this);
}

//��Ⱦ

void PlayerObject::loadActionFrame() {
	float textureWidth, textureHeight;//���Ŵ�С
	SDL_GetTextureSize(texture.get(), &textureWidth, &textureHeight);

	float frameWidth = attrs->player_sprite_frame_width;
	float frameHeight = attrs->player_sprite_frame_height;//��֡��С

	for (int row = 0;row * frameHeight < textureHeight;row++) {
		for (int col = 0;col * frameWidth < textureWidth;col++) {
			frames.push_back({ frameWidth * col,frameHeight * row, frameWidth,frameHeight });//ˮƽ���еľ����
		}
	}
}

SDL_FRect* PlayerObject::getActionFrameRect() {
	elapsed += Timer::Instance().getDeltaAdjustTime();
	if (elapsed >= (*spriteSheet)[currentState->GetState()].actionDelay) {

		if (++curFrame >= (*spriteSheet)[currentState->GetState()].endFrame) {
			setActionFrameStart();
		}
		if (curFrame >= frames.size()) {
			cout << "����������" << endl;
		}
		elapsed = 0;
	}

	return &frames[curFrame];
}

void PlayerObject::setActionFrameStart() {
	curFrame = (*spriteSheet)[currentState->GetState()].startFrame;
}

//void PlayerObject::Update() {
//	currentState->Update(*this);
//}































//
//PlayerObject::PlayerObject(const json& config){

//	playerAttrs->playerX = Resolution::Instance().getWindowRect().w / 2 - playerAttrs->player_render_width / 2;
//	playerAttrs->playerY = Resolution::Instance().getWindowRect().h / 2 - playerAttrs->player_render_height / 2;
//	SDL_FRect trect = {
//		playerAttrs->playerX,
//		playerAttrs->playerY,
//		playerAttrs->player_render_width,
//		playerAttrs->player_render_height
//	};
//
//	//Rect
//	shared_ptr<SDL_FRect> rect = std::make_shared<SDL_FRect>(trect);//��Ⱦ�����Ĵ�С,���ó�ʼλ��
//	hitBox = make_shared<Rect>(rect);
//
//
//	//actionFrameDelay
//	vector<float> actionframedelay = {};
//	actionFrameDelay = make_shared<std::vector<float>>(actionframedelay);
//	for (auto & val : config["actionFrameDelay"]) {
//			actionFrameDelay->push_back(val);
//	}

//
//	context = make_shared<Context>();//����������
//	context->initData("isOnGround",make_shared<bool>(false));//�Ƿ��ڵر���
//	context->initData("playerAttrs",playerAttrs);//�������
//	context->initData("interruptible_mask", make_shared<int>(0b00001111));
//
//	context->initData("playerState",make_shared<PlayerState>(PlayerState::Idle));//���״̬
//	playerState = context->getData<PlayerState>("playerState").get();
//	context->initData("rect",rect);//��Ҿ���
//	context->initData("spriteSheet", make_shared<std::unordered_map<PlayerState, SpriteSheet>>(spriteSheet));//��Ҿ����
//	context->initData("actionFrameDelay",actionFrameDelay);//��֡ʱ��
//	context->initData("texture", ResourceManager::Instance().getTexture(config["texture"]["catalog"],config["texture"]["fileName"]));//������ͼ
//	//setBehavior_tree(config["behavior_tree"], createNodeFromJson);//������Ϊ��
//	spritePlayer = make_shared<SpritePlayer>(context);//��ʼ������
//	context->initData("spritePlayer",spritePlayer);
//
//
//	bb = new BlackBoard();
//	root = make_unique<ParalleNode>();
//	auto selector = make_shared<Selector>();
//	selector->addChild(make_shared<MoveNode>(this,bb));
//
//
//
//	root->addChild(selector);
//
//
//
//
//}
//
//bool PlayerObject::setBehavior_tree(const json& config,function<shared_ptr<BTNode>(const json&,shared_ptr<Context>)> nodeFactory) {
//	root = make_unique<ParalleNode>();
//	for (auto& node : config["root"]["children"]) {
//		root->addChild(nodeFactory(node,context));
//	}
//	return true;
//}
//
//void PlayerObject::update() {
//	this->root->execute();
//}
//
//void PlayerObject::render()
//{
//	spritePlayer->update();
//	auto r = RendererManager::Instance().getRenderer();
//	SDL_SetRenderDrawColor(r,255,255,0,0);
//	auto& camera = Camera::Instance();
//	if (camera.isOnScreen(*hitBox->rect)) {
//		SDL_FRect rectInCamera = camera.worldToScreen(*hitBox->rect);
//		SDL_RenderRect(r,&rectInCamera);
//	}
//}
////��Ϊ�б�
//void PlayerObject::move() {
//	cout << "move" << endl;
//}
//
//
//
//
//
//
//
//
//
//
//PlayerAttrs& PlayerObject::getAttrs()
//{
//	return *context->getData<PlayerAttrs>("playerAttrs").get();
//}
//
//PlayerState PlayerObject::getState()
//{
//	return *playerState;
//}
//
//const std::string PlayerObject::printState() {
//	if (!playerState) {
//		return "playerState Ϊ��ָ��";
//	}
//	string state;
//	if ((bool)(*playerState & PlayerState::Idle)) {
//		state += "Idle";
//	}
//	if ((bool)(*playerState & PlayerState::Jump)) {
//		state += " Jump";
//	}
//	if ((bool)(*playerState & PlayerState::Down)) {
//		state += " Down";
//	}
//	if ((bool)(*playerState & PlayerState::Run)) {
//		state += " Run";
//	}
//	if ((bool)(*playerState & PlayerState::On_ground)) {
//		state += " On_ground";
//	}
//	return state;
//}
//
//void PlayerObject::setPlayerState(PlayerState playerState)
//{
//	*this->playerState |= playerState;
//}
//
//void PlayerObject::removePlayerState(PlayerState playerState)
//{
//	*this->playerState |= playerState;
//}
//
//void PlayerObject::resetState() {
//	*this->playerState = PlayerState::Idle;
//}
//
//SDL_FRect* PlayerObject::getRect() {
//	return hitBox->rect.get();
//}