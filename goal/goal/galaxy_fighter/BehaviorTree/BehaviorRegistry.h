#pragma once
#include "BTNode.h"

#define REGISTER_BEHAVIOR_NODE(nodeType) static bool nodeType##Registered = []() { BehaviorRegistry::Instance().Register("scalingUp", []() -> std::unique_ptr<BTNode> { return std::make_unique<scalingUp>(); }); return true; }();


using behaviorCreateFunc = std::function<std::unique_ptr<BTNode>()>;

class BehaviorRegistry
{
public:

	static BehaviorRegistry& Instance();

	void Register(const std::string& name, behaviorCreateFunc func);

	std::unique_ptr<BTNode> create(const string& name);
private:
	std::unordered_map < std::string, behaviorCreateFunc > registry;
};

