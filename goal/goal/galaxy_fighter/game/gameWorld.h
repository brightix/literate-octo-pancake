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
	void addNewObject(const string& s, BaseObject* newOBject);

	vector<BaseObject*>& getObjects();
	vector<BaseObject*>& getGroundObjects();
	//vector<BaseObject*>& getBulletObjects();
	//vector<BaseObject*>& getPlayerObjects();




	PlayerObject& getPlayer();

	WorldAttrs& getWorldAttrs();
	static GameWorld& Instance();
	void show_log();

	void show_log_on_screen();

	void developmentMode();

	void printError();
	void addError(std::string error);
	GameWorld(const GameWorld&) = delete;
	GameWorld& operator=(const GameWorld&) = delete;
private:

	GameWorld();
	~GameWorld();
	WorldAttrs worldAttrs;
	float log_interval;
	Camera* camera;
	PlayerObject* player;

	float report_log_time;
	std::vector<string> errorList;
	std::vector<BaseObject*> objects;
	std::vector<BaseObject*> GroundObjects;
	std::vector<BaseObject*> PlayerObjects;
	std::vector<BaseObject*> BulletObjects;
};