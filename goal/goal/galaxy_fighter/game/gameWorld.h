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
	static GameWorld& Instance();
	void show_log();

	void show_log_on_screen();

	GameWorld(const GameWorld&) = delete;
	GameWorld& operator=(const GameWorld&) = delete;
private:

	GameWorld();
	~GameWorld();
	WorldAttrs worldAttrs;
	float log_interval;
	Camera* camera;
	PlayerObject* player;
	Uint64 report_log_time;
};