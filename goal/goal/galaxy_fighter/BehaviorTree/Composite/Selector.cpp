#include "pch.h"
#include "Selector.h"

void Selector::addChild(shared_ptr<BTNode> BTNode) {
	children.emplace_back(BTNode);
}

bool Selector::execute() {
	for (auto& child : children) {
		if (child->execute() == true) {
			return true;
		}
	}
	return false;
}