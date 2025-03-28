#include "pch.h"
#include "AttackBox.h"
#include "../../FSM/Player/PlayerState.h"
#include "../../FSM/Player/SubState.h"
AttackBox::AttackBox(PlayerObject* from,string attackType) : BaseObject(ObjectType::Object_AttackBox)
{
	this->from = from;

	texture = ResourceManager::Instance().getTexture("player",attackType).get();
	SDL_FRect& fatherBox = from->getHitBox()->rect;
	hitBox = Rect(fatherBox,ColorManager::Instance().getColor(AttackColor));
	hitBox.rect = fatherBox;
	hitBox.rect.x = fatherBox.x + from->getOrientation() * fatherBox.w;
	hitBox.rect.y = fatherBox.y + fatherBox.h * 0.5;
	hitBox.rect.h = 50;
}

void AttackBox::on_collision(BaseObject* other)
{
	switch (other->getObjectType()) {
	case Object_Ground:
		if (isHitGround) {
			break;
		}
		isHitGround = true;
		//from->setEventVelocityX(-from->getOrientation() * 5000);
		from->ChangeSubState(new Rebound);


		break;
	case Object_Player:
		if (other != from) {
			if (auto* player = dynamic_cast<PlayerObject*>(other)) {
				player->ChangeState(new Hurt);
			}
		}
		break;
	default:
		break;
	}
}

void AttackBox::update()
{
	SDL_FRect& fatherBox = from->getHitBox()->rect;
	hitBox.rect.x = fatherBox.x + from->getOrientation() * fatherBox.w;
	hitBox.rect.y = fatherBox.y + fatherBox.h * 0.5;
	actionTime += Timer::Instance().getDeltaAdjustTime();
}

void AttackBox::render()
{
	auto& showRect = hitBox.rect;
	if (Camera::Instance().isOnScreen(showRect)) {
		SDL_FRect sr = Camera::Instance().worldToScreen(showRect);
		SDL_RenderTexture(RendererManager::Instance().getRenderer(),texture,nullptr,&sr);
	}
}

Rect* AttackBox::getHitBox()
{
	return &hitBox;
}

std::shared_ptr<SDL_FRect> AttackBox::getRenderRect()
{
	return std::shared_ptr<SDL_FRect>();
}

bool AttackBox::shouldDelete()
{
	return actionTime >= 0.2f;
}
