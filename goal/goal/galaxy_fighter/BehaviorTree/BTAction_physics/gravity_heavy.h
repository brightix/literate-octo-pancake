#pragma once
#include "../BTNode.h"
namespace BTAction_physics {
    class gravity_heavy :
        public BTNode
    {
    public:
        gravity_heavy(std::shared_ptr<Context> context);
        bool execute() override;
    };
}


