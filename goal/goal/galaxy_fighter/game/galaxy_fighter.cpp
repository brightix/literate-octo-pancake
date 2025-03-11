#include "pch.h"
#include "galaxy_fighter.h"
#include "../objects/environmentAssets/mapObject/MapObject.h"
#include "../objects/playerObject/Player_GreenTofu.h"

Galaxy_fighter::Galaxy_fighter(){
	camera = &Camera::getInstance();
	Resolution::getInstance().setResolution(2);
}

void Galaxy_fighter::loadResource() {
	ResourceManager& resource = ResourceManager::getInstance();
	background = make_unique<test_bk>(resource.get_bk()[3].get());
	camera->setCameraRange(background->getTexture());
	//player = make_unique<Player_lion>();
	player = make_unique<Player_GreenTofu>();
	camera->setCameraOwner(player.get());
}

void Galaxy_fighter::update() {
	player->update();
	camera->update();
	background->update();

	background->render();
	player->render();

	//for (auto& element :elements_dynamic) {
	//	element->execute();
	//}
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


		
		SDL_RenderPresent(renderer);

		//��־���
		gw.show_log();

		//��̬����֡��
		timer.sleep(timer.getRefreshTime());
	}
}