#include "pch.h"
#include "gravity_heavy.h"

using namespace BTAction_physics;



BTAction_physics::gravity_heavy::gravity_heavy(shared_ptr<Context> context) : BTNode(context)
{

}

bool gravity_heavy::execute(){

	if (getter()->getData<bool>("isPlayerOnground")) {
		return false;
	}
	auto attrs = getter()->getData<PlayerAttrs>("playerAttrs");
	attrs->playerY += *getter()->getData<float>("playerWeight").get() * GameWorld::getInstance().getWorldAttrs().gravity;
	if (attrs->playerY);	
	return true;
}
