#pragma once
#include "PlayerState.h"
class TransitionState :
    public PlayerState
{
    PlayerState* excessiveState;
    PlayerState* nextState;
    bool forceChange;
public:
    TransitionState(PlayerState* excessive, PlayerState* newState, bool forceChange) : excessiveState(excessive), nextState(newState), forceChange(forceChange) {}
    void Enter(PlayerObject& player) {
        if (forceChange) {
            player.ChangeState(nextState);
        }
        cout << "�������״̬" << endl;
    }

    void Update(PlayerObject& player) {
        excessiveState->Update(player);
        if (excessiveState->IsFinished()) {
            player.ChangeState(nextState);
        }
    }
    void Exit() {
        cout << "�˳����Ƚڵ�" << endl;
    }
};

