#include "pch.h"
#include "PlayerState.h"

void move(PlayerObject& player);
void demove(PlayerObject& player);
void render(PlayerObject& player);
void fall(PlayerObject& player);
void jump(PlayerObject& player,float strength);


class Move;
class Jump;
class Fall;
class Crouch;
class Hurt;
class LightAttack;
														//MoveLeft◊¥Ã¨
void IdleState::Enter(PlayerObject& player)
{
	player.setActionFrameStart();
}

void IdleState::Update(PlayerObject& player)
{
	if (player.IsLightAttack()) {
		player.ChangeState(new  LightAttack);
	}
	else if (player.IsMoving()) {
		player.ChangeState(new Move);
	}
	else if (!player.IsGrounded()) {
		player.ChangeState(new  Fall);
	}
	else if (player.IsJumping()) {
		player.ChangeState(new Jump);
	}
	else if(player.getVelocityX() != 0){
		demove(player);
	}
}

void IdleState::Render(PlayerObject& player)
{
	render(player);
}


void IdleState::Exit(PlayerObject& player)
{
}

std::string IdleState::GetState()
{
	return "Idle";
}
	


																				//Move ◊¥Ã¨

void Move::Enter(PlayerObject& player)
{
	player.setActionFrameStart();
}

void Move::Update(PlayerObject& player)
{
	if (player.IsLightAttack()) {
		player.ChangeState(new LightAttack);
	}
	else if (!player.IsGrounded()) {
		player.ChangeState(new Fall);
	}
	else if (player.IsJumping()) {
		player.ChangeState(new Jump);
	}
	else if (player.IsMoving()) {
		move(player);
	}
	else player.ChangeState(new IdleState);
}

void Move::Render(PlayerObject& player)
{
	render(player);
}

void Move::Exit(PlayerObject& player)
{
}

std::string Move::GetState()
{
	return "Move";
}


																		//Jump  ◊¥Ã¨
void Jump::Enter(PlayerObject& player)
{
	jump(player,player.getMaxJumpStrength());
	player.setActionFrameStart();
}

void Jump::Update(PlayerObject& player)
{
	if (player.IsLightAttack()) {
		player.ChangeState(new LightAttack);
	}
	else if(!player.IsJumping()) {
		player.setVelocityY(0);
		player.ChangeState(new Fall);
	}

	if (player.IsMoving()) {
		move(player);
	}
	else {
		demove(player);
	}
	if (player.IsJumping()) {
		fall(player);
		if (player.getVelocityY() > 0) {
			player.ChangeState(new Fall);
			return;
		}
	}
}

void Jump::Render(PlayerObject& player)
{
	render(player);
}

void Jump::Exit(PlayerObject& player)
{
}

std::string Jump::GetState()
{
	return "Jump";
}


																		//Fall  ◊¥Ã¨
void Fall::Enter(PlayerObject& player)
{
	player.setActionFrameStart();
	//player.setVelocityY(0);
}

void Fall::Update(PlayerObject& player)
{
	if (player.IsLightAttack()) {
		player.ChangeState(new LightAttack);
	}
	else if(player.IsGrounded()) {
		player.ChangeState(new IdleState);
	}
	if (player.IsMoving()) {
		move(player);
	}
	else {
		demove(player);
	}
	fall(player);
}

void Fall::Render(PlayerObject& player)
{
	render(player);
}

void Fall::Exit(PlayerObject& player)
{
}

std::string Fall::GetState()
{
	return "Fall";
}


void Hurt::Enter(PlayerObject& player)
{
}

void Hurt::Update(PlayerObject& player)
{
}

void Hurt::Render(PlayerObject& player)
{
}

void Hurt::Exit(PlayerObject& player)
{
}

std::string Hurt::GetState()
{
	return std::string();
}


															//LightAttack  ◊¥Ã¨
void LightAttack::Enter(PlayerObject& player)
{
	player.setActionFrameStart();
	SDL_FRect rect = player.getHitBox()->rect;
	rect.x = rect.x + player.getOrientation() * rect.w;
	attackBox = new AttackBox(&player, "attack_light.jpg");
	GameWorld::Instance().addNewObject("Attack", attackBox);
}

void LightAttack::Update(PlayerObject& player)
{
	if (player.IsMoving()) {
		move(player);
	}
	else {
		demove(player);
	}
	if(!player.IsGrounded()) {
		if (!player.IsJumping() && player.getVelocityY() < 0) {
			player.setVelocityY(0);
		}
		fall(player);
	}
	else if (player.IsJumping()) {
		jump(player,player.getMaxJumpStrength());
	}
	attackBox->update();
	if (attackBox->shouldDelete()) {
		player.ChangeState(new  IdleState);
	}
}

void LightAttack::Render(PlayerObject& player)
{
	render(player);
}

void LightAttack::Exit(PlayerObject& player)
{
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
		velocity *= exp(-friction * delta); // ÷∏ ˝À•ºı
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

void fall(PlayerObject& player) {
	float delta = Timer::Instance().getDeltaAdjustTime();
	float velocity = player.getVelocityY() + player.getGravity() * delta;
	velocity = min(velocity, 2000);
	player.setVelocityY(velocity);
}

void jump(PlayerObject& player,float strength) {
	player.setVelocityY(-strength);
}


void render(PlayerObject& player) {
	SDL_Texture* texture = player.getTexture().get();
	SDL_FRect* srcrect = player.getActionFrameRect();
	if (SDL_RenderTextureRotated(RendererManager::Instance().getRenderer(), texture, srcrect, player.getRenderRect().get(), 0, nullptr, player.getOrientation() > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL)) {
	}
	else {
		SDL_Log("‰÷»æŒ∆¿Ì ß∞‹");
	}
}

std::string Crouch::GetState()
{
	return "Crouch";
}


