#pragma once
#include "../../objects/playerObject/playerObject.h"


class SubState
{

public:
    virtual void Enter(PlayerObject& player) = 0;      // ����״̬
    virtual void Update(PlayerObject& player) = 0;     // ����״̬
    virtual void Exit(PlayerObject& player) = 0;       // �˳�״̬
    virtual ~SubState() = default;
    virtual bool IsFinished() { return true; }
    virtual std::string GetState() = 0;
};

class SubNone :
    public SubState
{
public:
    void Enter(PlayerObject& player);      // ����״̬
    void Update(PlayerObject& player);     // ����״̬
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
    void Enter(PlayerObject& player);      // ����״̬
    void Update(PlayerObject& player);     // ����״̬
    void Exit(PlayerObject& player);
    std::string GetState();

};

