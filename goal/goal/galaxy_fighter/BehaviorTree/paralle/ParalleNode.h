#pragma once
#include "../BTNode.h"
class ParalleNode : public BTNode
{
	std::vector<std::shared_ptr<BTNode>> children;
public:
	void addChild(std::shared_ptr<BTNode> child);
	bool execute() override;
};

