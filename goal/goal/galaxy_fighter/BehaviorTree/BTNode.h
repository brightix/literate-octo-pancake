#pragma once

class BTNode {
public:
	virtual ~BTNode() = default;
	virtual bool execute() = 0;
};