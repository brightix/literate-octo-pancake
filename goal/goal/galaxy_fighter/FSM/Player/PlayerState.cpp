#include "pch.h"
#include "PlayerState.h"

void move(PlayerObject& player);
void demove(PlayerObject& player);
void render(PlayerObject& player);

																			//MoveLeft状态
void IdleState::Enter(PlayerObject& player)
{
	cout << "进入 Idle" << endl;
	player.setActionFrameStart();
}

void IdleState::Update(PlayerObject& player)
{
	if (player.IsMoving()) {
		player.ChangeState(new Move);
	}
	else if (player.IsJumping()) {
		player.ChangeState(new Jump);
	}
	else if (!player.IsGrounded()) {
		player.ChangeState(new Fall);
	}
	else if(player.getVelocityX() != 0){
		demove(player);
	}
	else if (player.IsLightAttack()) {
		player.ChangeState(new LightAttack);
	}
}

void IdleState::Render(PlayerObject& player)
{
	render(player);
}


void IdleState::Exit(PlayerObject& player)
{
	//cout << "退出 Idle" << endl;
}

std::string IdleState::GetState()
{
	return "Idle";
}
	


																				//Move 状态

void Move::Enter(PlayerObject& player)
{
	cout << "进入 Move" << endl;
	player.setActionFrameStart();
}

void Move::Update(PlayerObject& player)
{
	if (!player.IsGrounded()) {
		player.ChangeState(new Fall);
	}
	else if (player.IsJumping()) {
		player.ChangeState(new Jump);
	}
	else if (player.IsMoving()) {
		move(player);
	}
	else {
		player.ChangeState(new IdleState);
	}
}

void Move::Render(PlayerObject& player)
{
	render(player);
}

void Move::Exit(PlayerObject& player)
{
	//cout << "退出 Move" << endl;
}

std::string Move::GetState()
{
	return "Move";
}


																		//Jump  状态
void Jump::Enter(PlayerObject& player)
{
	cout << "进入 Jump" << endl;
	player.setVelocityY(-player.getMaxJumpStrength());
	player.setActionFrameStart();
}

void Jump::Update(PlayerObject& player)
{
	if (player.IsMoving()) {
		move(player);
	}
	else {
		demove(player);
	}
	if (player.IsJumping()) {
		auto delta = Timer::Instance().getDeltaAdjustTime();
		float velocity = player.getVelocityY() + player.getAccelerationY() * delta;
		if (velocity > 0) {
			player.ChangeState(new Fall);
			return;
		}
		player.setVelocityY(velocity);
	}
	else if (player.IsGrounded()) {
		player.ChangeState(new IdleState);
	}
	else {
		player.ChangeState(new Fall);
	}
}

void Jump::Render(PlayerObject& player)
{
	render(player);
}

void Jump::Exit(PlayerObject& player)
{
	//cout << "退出 Jump" << endl;
}

std::string Jump::GetState()
{
	return std::string();
}


																		//Fall  状态
void Fall::Enter(PlayerObject& player)
{
	cout << "进入 Fall" << endl;
	player.setActionFrameStart();
	player.setVelocityY(0);
}

void Fall::Update(PlayerObject& player)
{
	if (player.IsMoving()) {
		move(player);
	}
	else {
		demove(player);
	}
	if (!player.IsGrounded()) {
		float delta = Timer::Instance().getDeltaAdjustTime();
		float velocity = player.getVelocityY() + player.getGravity() * delta;
		velocity = min(velocity, 2000);
		player.setVelocityY(velocity);
	}
	else {
		player.ChangeState(new IdleState);
	}
}

void Fall::Render(PlayerObject& player)
{
	render(player);
}

void Fall::Exit(PlayerObject& player)
{
	//cout << "退出 Fall" << endl;
}

std::string Fall::GetState()
{
	return "Fall";
}

															//Fall  状态
void LightAttack::Enter(PlayerObject& player)
{
	cout << "进入 LightAttack" << endl;
	player.setActionFrameStart();
	player.setVelocityX(0);
	hitBox = Rect({ player.getPositionX(),player.getPositionY(),0,player.getRenderRect()->h });

}

void LightAttack::Update(PlayerObject& player)
{
	if (player.IsMoving()) {
		move(player);
	}
	else {
		demove(player);
	}
	actionTime += Timer::Instance().getDeltaAdjustTime();
	if (actionTime < 0.5) {
		hitBox.rect.w = actionTime * player.getMaxLightAttackRange();
	}
	else if(actionTime < 1.0){
		hitBox.rect.w = (1 - actionTime) * player.getMaxLightAttackRange();
	}
	else{
		player.ChangeState(new IdleState);
	}
}

void LightAttack::Render(PlayerObject& player)
{
	render(player);
}

void LightAttack::Exit(PlayerObject& player)
{
	//cout << "退出 Fall" << endl;
}

std::string LightAttack::GetState()
{
	return "LightAttack";
}





void move(PlayerObject& player) {
	int orientation = player.IsMovingLeft() ? -1 : 1;
	if (orientation != player.getOrientation() || player.getVelocityX() == 0) {
		player.setOrientation(orientation);
		player.setVelocityX(orientation * 1);
	}
	auto delta = Timer::Instance().getDeltaAdjustTime();
	float MaxRunStrength = player.getMaxRunStrength();
	float velocity = player.getVelocityX() + orientation * player.getAccelerationX() * delta;
	velocity = clamp(velocity, -MaxRunStrength, MaxRunStrength);
	player.setVelocityX(velocity);
}

void demove(PlayerObject& player) {
	float velocity = player.getVelocityX();
	float delta = Timer::Instance().getDeltaAdjustTime();
	float friction = player .getFriction();
	if (velocity > 0) {
		velocity *= exp(-friction * delta); // 指数衰减
		if (velocity < 0.1) {	
			velocity = 0;
		}
	}
	else if (velocity < 0) {
		velocity *= exp(-friction * delta);
		//velocity += friction * log(1 + delta) * delta;
		if (velocity > 0.1) {
			velocity = 0;
		}
	}
	player.setVelocityX(velocity);
}

void render(PlayerObject& player) {
	SDL_Texture* texture = player.getTexture().get();
	SDL_FRect* srcrect = player.getActionFrameRect();
	if (SDL_RenderTextureRotated(RendererManager::Instance().getRenderer(), texture, srcrect, player.getRenderRect().get(), 0, nullptr, player.getOrientation() > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL)) {
	}
	else {
		SDL_Log("渲染纹理失败");
	}
}

std::string Crouch::GetState()
{
	return "Crouch";
}
