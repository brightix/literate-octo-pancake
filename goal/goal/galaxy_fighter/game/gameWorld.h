#pragma once
#include "pch.h"
#include "../objects/PlayerObject/PlayerObject.h"
#include "../objects/BaseObject.h"
#include "../objects/camera/Camera.h"


typedef struct WorldAttrs{
	float gravity;
}WorldAttrs;

class GameWorld {
	
public:
	void setWorld(const nlohmann::json& config);
	void setPlayer(PlayerObject* h);
	void setCamera(Camera* camera);
	PlayerObject& getPlayer();

	WorldAttrs& getWorldAttrs();
	static GameWorld& getInstance();
	void show_log();

	GameWorld(const GameWorld&) = delete;
	GameWorld& operator=(const GameWorld&) = delete;
private:

	GameWorld() = default;
	~GameWorld();
	WorldAttrs worldAttrs;
	Camera* camera;
	PlayerObject* player;
	Uint64 report_log_time;
};