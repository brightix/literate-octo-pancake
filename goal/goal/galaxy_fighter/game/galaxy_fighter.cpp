#include "pch.h"
#include "galaxy_fighter.h"
#include "../objects/environmentAssets/mapObject/MapObject.h"
#include "../objects/environmentAssets/groundObject/GroundObject.h"
#include "../core/physics/QuadTree.h"
#include "../objects/UI/UIManager/UIManager.h"
using json = nlohmann::json;

void Galaxy_fighter::loadResource() {
	ResourceManager& resource = ResourceManager::Instance();
	GameWorld& gw = GameWorld::Instance();

	ifstream file("config.json");
	json config;
	file >> config;
	GameWorld::Instance().setWorld(config["world"]);
	ui = UI();
	background = make_unique<MapObject>(config["background"]);
	camera->setCameraRange(background->getWholeRect());

	player = make_shared<PlayerObject>(config["player_tofu"]);

	camera->setCameraOwner(player.get());
	gw.addNewObject("player",player.get());
	gw.addNewObject("ground", new GroundObject(0, 1000, 1));
	gw.addNewObject("ground", new GroundObject(300, 700, 0.03));

	gw.addNewObject("ground", new GroundObject(-3400,0, 1));
	gw.addNewObject("ground", new GroundObject(1500, 500, 1));
	gw.addNewObject("ground", new GroundObject(1500, 400, 0.1));
	gw.addNewObject("ground", new GroundObject(1200, 800, 0.1));
	gw.addNewObject("ground", new GroundObject(800, 600, 0.1));
	gw.addNewObject("ground", new GroundObject(1200, 400, 0.1));
	gw.addNewObject("ground", new GroundObject(300, 400, 0.1));

	gw.addNewObject("ground", new GroundObject(200, 800, 0.1));
	//objects.push_back(new GroundObject(400, 750, 0.1));
}

void Galaxy_fighter::update() {
	vector<BaseObject*>& objects = GameWorld::Instance().getObjects();
	//逻辑层
	background->render();

	UIManager& uiManager = UIManager::Instance();
	uiManager.refreshEscButton();
	if (uiManager.isUiStackEmpty()) {
		ui.update();
		background->update();
		player->update();
		player->resetActionState();
		QuadTreeManager::Instance().getQtree().update_collision(objects);

		camera->update();
		player->refreshRenderRect();
	}

	for (auto o : objects) {
		o->render();
	}
	checkDevelopmentMode();
	uiManager.update();
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
	bool isInfiniteFrame = false;
	while (running) {
		timer.update();
		SDL_Event event;
		//处理输入
		input.postUpdate();
		while (SDL_PollEvent(&event)) {
			if (!input.update(event)) {
				running = false;
				break;
			}
		}
		if (!running) {
			//保存数据
			break;
		}

		input.checkAllKeyEvents();

		//渲染部分
		SDL_RenderClear(renderer);


		update();


		SDL_RenderPresent(renderer);


		//日志输出
		
		//动态调整帧率
		timer.sleep(timer.getRefreshTime());
	}
}

Galaxy_fighter::Galaxy_fighter() {
	InputManager::Instance().switchToEnglishInput();
	camera = &Camera::Instance();
	Resolution::Instance().setResolution(2);
	std::ios::sync_with_stdio(false);
}

void Galaxy_fighter::checkDevelopmentMode() {
	InputManager& input = InputManager::Instance();
	if (input.isKeyPressedOnce(SDL_SCANCODE_F1)) {
		isDevelopmentEnable = !isDevelopmentEnable;
	}
	if (!isDevelopmentEnable) {
		auto& gw = GameWorld::Instance();
		gw.developmentMode();
		gw.show_log();
	}
}


void Galaxy_fighter::loaaGameWorld() {
	GameWorld& gw = GameWorld::Instance();
	gw.setCamera(camera);
	gw.setPlayer(player.get());
	QuadTreeManager::Instance().init(Camera::Instance().getCameraRange());
}