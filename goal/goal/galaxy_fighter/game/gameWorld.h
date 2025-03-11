#pragma once
#include "pch.h"
#include "../objects/PlayerObject/PlayerObject.h"
#include "../objects/BaseObject.h"
#include "../objects/camera/Camera.h"


class GameWorld {
	
public:
	void setPlayer(PlayerObject* h);
	void setCamera(Camera* camera);
	PlayerObject& getPlayer();

	static GameWorld& getInstance();
	void show_log();
	GameWorld(const GameWorld&) = delete;
	GameWorld& operator=(const GameWorld&) = delete;
private:
	GameWorld();
	~GameWorld();
	Camera* camera;
	PlayerObject* player;
	Uint64 report_log_time;
};