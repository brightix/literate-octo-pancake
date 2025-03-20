#include "pch.h"
#include "galaxy_fighter.h"
#include "../objects/environmentAssets/mapObject/MapObject.h"
#include "../objects/environmentAssets/groundObject/GroundObject.h"
#include "../core/physics/QuadTree.h"
#include "../objects/UI/UIManager/UIManager.h"
using json = nlohmann::json;

Galaxy_fighter::Galaxy_fighter(){
	camera = &Camera::Instance();
	Resolution::Instance().setResolution(2);
}

void Galaxy_fighter::loadResource() {
	ResourceManager& resource = ResourceManager::Instance();
	ifstream file("config.json");
	json config;
	file >> config;
	GameWorld::Instance().setWorld(config["world"]);
	ui = UI();
	background = make_unique<MapObject>(config["background"]);
	camera->setCameraRange(background->getWholeRect());

	player = make_shared<PlayerObject>(config["player_tofu"]);

	camera->setCameraOwner(player.get());
	objects.push_back(new GroundObject(200, 800, 0.1));
	objects.push_back(new GroundObject(1000, 700, 0.03));
	objects.push_back(new GroundObject(400, 750, 0.1));
	objects.push_back(new GroundObject(0,1000,1));
	objects.push_back(player.get());
}

void Galaxy_fighter::update() {
	//�߼���
	background->render();
	ui.update();
	UIManager& uiManager = UIManager::Instance();
	if (uiManager.isUiStackEmpty()) {
		background->update();
		player->update();
		player->resetActionState();
		qtree.update_collision(objects);
		player->refreshRenderRect();
		camera->update();
	}

	RendererManager::Instance().renderTexture("player","girl_1_normal.png",1);//������
	for (auto o : objects) {
		o->render();
	}
	uiManager.update();
}

void Galaxy_fighter::loaaGameWorld() {
	GameWorld& gw = GameWorld::Instance();
	gw.setCamera(camera);
	gw.setPlayer(player.get());
	qtree = QuadTree(0, Camera::Instance().getCameraRange());
}

void Galaxy_fighter::play(){
	Camera& camera = Camera::Instance();
	RendererManager& rendererM = RendererManager::Instance();
	SDL_Renderer* renderer = RendererManager::Instance().getRenderer();
	ResourceManager& resource = ResourceManager::Instance();
	Timer& timer = Timer::Instance();
	InputManager& input = InputManager::Instance();
	
	GameWorld& gw = GameWorld::Instance();






	bool running = true;
	loadResource();
	loaaGameWorld();
	while (running) {
		timer.update();
		SDL_Event event;
		//��������
		while (SDL_PollEvent(&event)) {
			if (!input.update(event)) {
				running = false;
				break;
			}
		}
		input.postUpdate();
		if (!running) {
			//��������
			break;
		}

		input.isSpacePressed();
		input.checkAllKeyEvents();

		//��Ⱦ����
		SDL_RenderClear(renderer);


		update();


		gw.show_log_on_screen();
		SDL_RenderPresent(renderer);

		//��־���
		gw.show_log();

		//��̬����֡��
		timer.sleep(timer.getRefreshTime());
	}
}