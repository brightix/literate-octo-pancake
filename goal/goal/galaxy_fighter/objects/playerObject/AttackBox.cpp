#include "pch.h"
#include "AttackBox.h"
#include "../../FSM/Player/PlayerState.h"
AttackBox::AttackBox(BaseObject* from,string attackType,SDL_FRect rect) : BaseObject(ObjectType::Object_AttackBox)
{
	this->from = from;
	texture = ResourceManager::Instance().getTexture("player",attackType).get();
	hitBox = Rect(rect);
}

void AttackBox::on_collision(shared_ptr<BaseObject> other)
{
	switch (other->getObjectType()) {
	case Object_Ground:
		break;
	case Object_Player:
		if (other.get() != from) {
			if (auto* player = dynamic_cast<PlayerObject*>(other.get())) {
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
	return actionTime >= 1.0;
}
