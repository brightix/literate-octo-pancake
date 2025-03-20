#pragma once
#include "../core/Context.h"

class BTNode {
public:
	virtual ~BTNode() = default;
	virtual bool execute() = 0;
};