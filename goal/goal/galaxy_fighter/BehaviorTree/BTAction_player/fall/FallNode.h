#pragma once
#include "../../BTNode.h"
class FallNode :
    public BTNode
{
    PlayerObject* player;
public:
    FallNode(PlayerObject* player);
    bool execute();
};

