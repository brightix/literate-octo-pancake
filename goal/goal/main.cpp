#include "menu.h"

#define REGISTER_BEHAVIOR_NODE(nodeType) static bool nodeType##Registered = []() { BehaviorRegistry::getInstance().Register("scalingUp", []() -> std::unique_ptr<BTNode> { return std::make_unique<scalingUp>(); }); return true; }();

int main() {

	Menu menu;
	//menu.welcome();
	menu.startGame();
	return 0;
}