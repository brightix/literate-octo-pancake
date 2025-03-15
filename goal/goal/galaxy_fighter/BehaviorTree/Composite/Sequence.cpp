#include "pch.h"
#include "Sequence.h"

void Sequence::addChild(shared_ptr<BTNode> BTNode) {
	children.emplace_back(move(BTNode));
}

bool Sequence::execute() {
	for (auto& it : children) {
		if (it->execute() == false) {
			return false;
		}
	}
	return true;
}