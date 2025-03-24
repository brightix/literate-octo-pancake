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
	void setObjects(std::vector<shared_ptr<BaseObject>>* objects);
	void addNewObject(const string& s, shared_ptr<BaseObject> newOBject);

	vector<shared_ptr<BaseObject>>& getObjects();
	vector<shared_ptr<BaseObject>>& getGroundObjects();
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
	std::vector<shared_ptr<BaseObject>> objects;
	std::vector<shared_ptr<BaseObject>> GroundObjects;
	std::vector<shared_ptr<BaseObject>> PlayerObjects;
	std::vector<shared_ptr<BaseObject>> BulletObjects;
};