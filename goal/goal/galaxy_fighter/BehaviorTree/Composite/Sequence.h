#pragma once
#include "../BTNode.h"
class Sequence : public BTNode
{
	vector<shared_ptr<BTNode>> children;
public:
	void addChild(shared_ptr<BTNode> BTNode);
	bool execute() override;
};

