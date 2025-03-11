#include "pch.h"
#include "Selector.h"

void Selector::addChild(unique_ptr<BTNode> BTNode) {
	children.emplace_back(move(BTNode));
}

bool Selector::execute() {
	for (auto& child : children) {
		if (child->execute() == true) {
			return true;
		}
	}
	return false;
}