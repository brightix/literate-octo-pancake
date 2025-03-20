#pragma once
#include "../../../objects/playerObject/playerObject.h"
#include "../../BTNode.h"
#include "../../../core/BlackBoard.h"

class MoveNode : public BTNode {
private:
    PlayerObject* player;
public:
    MoveNode(PlayerObject* player);
    bool execute();
};

