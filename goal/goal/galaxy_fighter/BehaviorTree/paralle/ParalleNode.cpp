#include "pch.h"
#include "ParalleNode.h"

void ParalleNode::addChild(unique_ptr<BTNode> child) {
	children.emplace_back(move(child));
}

bool ParalleNode::execute() {
	for (auto& child : children) {
		child->execute();
	}
	return false;
}
