#include "pch.h"
#include "menu.h"
#include "galaxy_fighter/game/galaxy_fighter.h"
#include "./galaxy_fighter/objects/MainMenuObject/MenuImage.h"

Menu::Menu() {
	running = true;
	SDL_Init(SDL_INIT_VIDEO);
	playing_game = nullptr;
}

void Menu::init() {
	Resolution::getInstance();
	RendererManager::getInstance();
	ResourceManager::getInstance();
}

void Menu::loadResource() {
	ResourceManager& resource = ResourceManager::getInstance();
	TextRenderer& textRenderer = TextRenderer::getInstance();


	//bk = move(make_unique<MenuBackground>(resource.get_bk()[0].get()));
	//logoList.emplace_back(make_unique<MenuButton>(resource.get_game_logo()[0].get(), 0.1f, swidth * 0.1, sheight * 0.7));
	//logoList.emplace_back(make_unique<MenuButton>(resource.get_game_logo()[1].get(), 0.1f, swidth * 0.25, sheight * 0.7));
	//logoList.emplace_back(make_unique<MenuButton>(resource.get_game_logo()[2].get(), 0.1f, swidth * 0.4, sheight * 0.7));
	//logoList.emplace_back(make_unique<MenuButton>(textRenderer.getTextTexture("Start"), 1.0f, swidth * 0.8, sheight * 0.5));
}

void Menu::destroy() {
	logoList.clear();
	bk.reset();
}

void Menu::update() {
	//TextRenderer& textRenderer = TextRenderer::getInstance();
	//sort(logoList.begin(), logoList.end(), [&](auto& a,auto& b) {
	//	return a->getRect().w < b->getRect().w ;
	//	});
	//bk->update();
	//for (auto& logo : logoList) {
	//	logo->update();
	//}

	
	//textRenderer.renderText(swidth*0.05,sheight*0.9,textRenderer.getTextTexture("VER 0.0.1"));
}
void Menu::welcome() {
	init();
	Timer& timer = Timer::getInstance();
	InputManager& input = InputManager::getInstance();
	GameWorld& gw = GameWorld::getInstance();
	Resolution& resolution = Resolution::getInstance();
	TextRenderer& textRenderer = TextRenderer::getInstance();
	ResourceManager& resource = ResourceManager::getInstance();//资源管理

	SDL_Renderer* renderer = RendererManager::getInstance().getRenderer();

	loadResource();
	while (running) {
		timer.update();
		SDL_Event event;
		//处理输入
		while (SDL_PollEvent(&event)) {
			if (!input.update(event)) {
				running = false;
				break;
			}
		}
		input.postUpdate();
		if (!running) {
			//保存数据
			break;
		}
		input.isSpacePressed();
		input.checkAllKeyEvents();

		//渲染部分
		SDL_RenderClear(renderer);


		update();


		SDL_RenderPresent(renderer);

		//日志输出
		gw.show_log();

		switch (selectGame()) {
		case galaxy_fighter:
		case mind_clear:
		case monster_hunter:
			playing_game = new Galaxy_fighter;
			playing_game->play();
			init();
			break;
		default:
			break;
		}
		game_clean(&playing_game);
		//动态调整帧率
		timer.sleep(timer.getRefreshTime());
	}


};

game_name Menu::selectGame() {
	InputManager& input = InputManager::getInstance();
	for (int i = 0;i < logoList.size();i++) {
		if (input.isPointInRect(logoList[i]->getRect())) {
			destroy();
			return static_cast<game_name>(i);
		}
	}
	return none_selected;
}

void Menu::game_clean(GameObject** game) {
	if (*game) {
		delete *game;
		*game = nullptr;
		loadResource();
	}

}


Menu::~Menu() {
	SDL_Quit();
	cout << "程序关闭..." << endl;
}

void Menu::startGame() {
	playing_game = new Galaxy_fighter;
	playing_game->play();
}