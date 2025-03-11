#pragma once
#include "../BTNode.h"

class Selector : public BTNode
{
	vector<unique_ptr<BTNode>> children;
public:
	void addChild(unique_ptr<BTNode> BTNode);
	bool execute() override;
};

