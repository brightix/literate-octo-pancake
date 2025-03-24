#pragma once
#include "pch.h"
#include "../../objects/playerObject/playerObject.h"
#include "../../core/physics/QuadTree.h"

class MoveLeft;
class MoveRight;
class Jump;
class Crouch;

class PlayerObject;

class PlayerState
{

public:
    virtual void Enter(PlayerObject& player) = 0;      // ����״̬
    virtual void Update(PlayerObject& player) = 0;     // ����״̬
    virtual void Render(PlayerObject& player) = 0;
    virtual void Exit(PlayerObject& player) = 0;       // �˳�״̬
    virtual ~PlayerState() = default;
    virtual bool IsFinished() { return true; }
    virtual std::string GetState() = 0;
};

class IdleState :
    public PlayerState
{
public:
    void Enter(PlayerObject& player);
    void Update(PlayerObject& player);
    void Render(PlayerObject& player);
    void Exit(PlayerObject& player);
    std::string GetState();
};

class Move :
    public PlayerState
{
public:
    void Enter(PlayerObject& player);
    void Update(PlayerObject& player);
    void Render(PlayerObject& player);
    void Exit(PlayerObject& player);
    std::string GetState();
};

class Jump :
    public PlayerState
{
public:
    void Enter(PlayerObject& player);
    void Update(PlayerObject& player);
    void Render(PlayerObject& player);
    void Exit(PlayerObject& player);
    std::string GetState();
};

class Fall :
    public PlayerState
{
public:
    void Enter(PlayerObject& player);
    void Update(PlayerObject& player);
    void Render(PlayerObject& player);
    void Exit(PlayerObject& player);
    std::string GetState();
};

class Crouch :
    public PlayerState
{
public:
    void Enter(PlayerObject& player);
    void Update(PlayerObject& player);
    void Render(PlayerObject& player);
    void Exit(PlayerObject& player);
    std::string GetState();
};

class LightAttack :
    public PlayerState
{
    float actionTime = 0;
    Rect hitBox;
public:
    void Enter(PlayerObject& player);
    void Update(PlayerObject& player);
    void Render(PlayerObject& player);
    void Exit(PlayerObject& player);
    std::string GetState();
};