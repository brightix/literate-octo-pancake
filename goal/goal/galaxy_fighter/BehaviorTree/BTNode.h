#pragma once
#include "../core/Context.h"

class BTNode {
private:
	std::shared_ptr<Context> context;
public:
	BTNode() = default;
	BTNode(std::shared_ptr<Context> ctx);
	virtual ~BTNode() = default;
	virtual bool execute() = 0;
	std::shared_ptr<Context> getter() {
		return context;
	}
};