#pragma once
#include "BTNode.h"

class BehaviorTree:public BTNode
{
	unique_ptr<BTNode> root;
public:
	BehaviorTree(const string& behaviorName);
	bool execute();
};

