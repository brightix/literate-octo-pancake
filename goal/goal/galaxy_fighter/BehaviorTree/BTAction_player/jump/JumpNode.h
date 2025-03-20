#pragma once
#include "../../BTNode.h"
class JumpNode : public BTNode
{
    PlayerObject* player;
public:
    JumpNode(PlayerObject* player);
    bool execute();
};

