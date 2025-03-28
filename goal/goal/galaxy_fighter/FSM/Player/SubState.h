#pragma once
#include "../../objects/playerObject/playerObject.h"


class SubState
{

public:
    virtual void Enter(PlayerObject& player) = 0;      // 进入状态
    virtual void Update(PlayerObject& player) = 0;     // 更新状态
    virtual void Exit(PlayerObject& player) = 0;       // 退出状态
    virtual ~SubState() = default;
    virtual bool IsFinished() { return true; }
    virtual std::string GetState() = 0;
};

class SubNone :
    public SubState
{
public:
    void Enter(PlayerObject& player);      // 进入状态
    void Update(PlayerObject& player);     // 更新状态
    void Exit(PlayerObject& player);
    std::string GetState();
};

class Rebound :
    public SubState
{
    float acceleration;
    int orientation;
    double actionTime;
    double elapsed;
    ~Rebound();
public:
    void Enter(PlayerObject& player);      // 进入状态
    void Update(PlayerObject& player);     // 更新状态
    void Exit(PlayerObject& player);
    std::string GetState();

};

