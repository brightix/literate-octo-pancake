#pragma once
#include "../../BTNode.h"
class DownNode :
    public BTNode
{
    PlayerObject* player;

public:
    DownNode(PlayerObject* player);
    bool execute();
};

