#pragma once
#include "pch.h"
#include "../gameObject/gameObject.h"
#include "../objects/camera/Camera.h"
#include "../objects/environmentAssets/mapObject/MapObject.h"
#include "../core/physics/QuadTree.h"
#include "../objects/UI/UI.h"
class Galaxy_fighter : public GameObject {
public:
	Galaxy_fighter();
	void play();
	void update();



private:
	void loaaGameWorld();
	void loadResource();
	void checkDevelopmentMode();

	unique_ptr<MapObject> background;
	shared_ptr<PlayerObject> player;
	vector<BaseObject*> objects;
	//vector<unique_ptr<BTNode>> elements_dynamic;
	Camera* camera;
	QuadTree qtree;
	UI ui;
	bool isDevelopmentEnable = false;
};

