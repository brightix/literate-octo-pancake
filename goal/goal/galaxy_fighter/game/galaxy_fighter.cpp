#include "pch.h"
#include "galaxy_fighter.h"
#include "../objects/environmentAssets/mapObject/MapObject.h"
#include "../objects/playerObject/Player_GreenTofu.h"
using json = nlohmann::json;

Galaxy_fighter::Galaxy_fighter(){
	camera = &Camera::getInstance();
	Resolution::getInstance().setResolution(2);
}

void Galaxy_fighter::loadResource() {
	ResourceManager& resource = ResourceManager::getInstance();
	ifstream file("config.json");
	json config;
	file >> config;
	GameWorld::getInstance().setWorld(config["world"]);
	background = make_unique<MapObject>(config["background"]);
	camera->setCameraRange(background->getWholeRect());

	player = make_shared<PlayerObject>(config["player_tofu"]);

	camera->setCameraOwner(player.get());
}

void Galaxy_fighter::update() {
	player->update();
	camera->update();
	background->update();

	background->render();
	RendererManager::getInstance().renderTexture("player","girl_1_normal.png",1);
	player->render();

}

void Galaxy_fighter::loaaGameWorld() {
	GameWorld& gw = GameWorld::getInstance();
	gw.setCamera(camera);
	gw.setPlayer(player.get());
}

void Galaxy_fighter::play(){
	
	RendererManager& rendererM = RendererManager::getInstance();
	SDL_Renderer* renderer = RendererManager::getInstance().getRenderer();
	ResourceManager& resource = ResourceManager::getInstance();
	Timer& timer = Timer::getInstance();
	InputManager& input = InputManager::getInstance();
	
	GameWorld& gw = GameWorld::getInstance();




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