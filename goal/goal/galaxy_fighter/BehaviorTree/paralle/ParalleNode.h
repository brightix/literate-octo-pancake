#pragma once
#include "../BTNode.h"
class ParalleNode : public BTNode
{
	std::vector<std::unique_ptr<BTNode>> children;
public:
	void addChild(std::unique_ptr<BTNode> child);
	bool execute() override;
};

