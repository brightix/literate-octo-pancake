#pragma once
#include "../BTNode.h"

class Decorator :
    public BTNode
{
protected:
	std::unique_ptr<BTNode> child;
public:
	Decorator(std::unique_ptr<BTNode> child);
};

