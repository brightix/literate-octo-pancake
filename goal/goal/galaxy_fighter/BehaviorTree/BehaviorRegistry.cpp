#include "pch.h"
#include "BehaviorRegistry.h"

BehaviorRegistry& BehaviorRegistry::getInstance() {
	static BehaviorRegistry instance;
	return instance;
}

void BehaviorRegistry::Register(const std::string& name, behaviorCreateFunc func) {
	registry[name] = func;

}

std::unique_ptr<BTNode> BehaviorRegistry::create(const string& name) {
	if (registry.count(name)) {
		return registry[name]();
	}
	return nullptr;
}