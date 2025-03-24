#pragma once
#include "pch.h"

class Rect;

enum ObjectType {
	Player,
	Enemy,
	Ground,
	Bullet
};

class BaseObject
{
private:
	ObjectType type;
public:
	BaseObject(ObjectType type) : type(type) {}
	virtual ~BaseObject() = default;

	virtual void update() = 0;
	virtual void render() = 0;
	virtual Rect* getHitBox() = 0;
	virtual std::shared_ptr<SDL_FRect> getRenderRect() = 0;
	virtual void on_collision(BaseObject* other) = 0;
	virtual bool hasMoved() { return false; }
	virtual ObjectType getObjectType() {
		return type;
	};
};

