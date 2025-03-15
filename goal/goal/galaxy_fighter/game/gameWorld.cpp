#include "pch.h"
#include "gameWorld.h"
#include "../core/Resolution.h"

void GameWorld::setWorld(const nlohmann::json& config) {
	worldAttrs.gravity = config["gravity"];
}

WorldAttrs& GameWorld::getWorldAttrs()
{
	return worldAttrs;
}

void GameWorld::setPlayer(PlayerObject* h){ player = h; }

void GameWorld::setCamera(Camera* camera) { this->camera = camera; }

PlayerObject& GameWorld::getPlayer() { return *player; }



GameWorld& GameWorld::getInstance() {
	static GameWorld instance;
	return instance;
}

void GameWorld::show_log() {
	Timer& t = Timer::getInstance();
	report_log_time += t.getDeltaTime();
	if (report_log_time >= LOG_TIME_INTERVAL) {
		SDL_Time currentT;
		SDL_DateTime dt;
		SDL_GetCurrentTime(&currentT);
		SDL_TimeToDateTime(currentT, &dt, true);
		cout << endl << endl << endl;
		cout << "+---" << dt.year << "/" << dt.month << "/" << dt.day << "   " << dt.hour << ":" << dt.minute << ":" << dt.second << "---------------- * * * ---" << endl;;
		cout << "| 帧间隔     :" << t.getDeltaTime() << endl;

		if (player)
		{
			cout << "| 玩家状态   :" << player->printState() << endl;
			cout << "| 玩家坐标x  :" << (short)player->getAttrs().playerX << ", y:" << (short)player->getAttrs().playerY << endl;

		}
		if(camera)
			cout << "| 相机坐标x  :" << (short)camera->getViewport()->x << ", y:" << (short)camera->getViewport()->y << endl;
		cout << "| 分辨率     :" << Resolution::getInstance().getWindowRect().w << " x " << Resolution::getInstance().getWindowRect().h << endl;
		cout << "+------------------------------------------------" << endl;
		report_log_time = 0;
	}
}

void GameWorld::show_log_on_screen() {
	TextRenderer& textRenderer = TextRenderer::getInstance();
	Timer& t = Timer::getInstance();
	SDL_Renderer* renderer = RendererManager::getInstance().getRenderer();
	SDL_Texture* texture;
	textRenderer.setColor(200,200,200,255);
	int i = 0;
	
	//帧率
	texture = textRenderer.getTextTexture("帧数:" + to_string((int)(1000 / t.getDeltaTime())), "pixel_12", 40);
	SDL_FRect dstRect = { 0,i++ * log_interval,0,0 };
	SDL_GetTextureSize(texture, &dstRect.w, &dstRect.h);
	SDL_RenderTexture(renderer, texture, nullptr, &dstRect);

	//玩家信息
	if (player) {
		texture = textRenderer.getTextTexture("玩家坐标 x:" + to_string((int)player->getAttrs().playerX) + ", y : " + to_string((int)player->getAttrs().playerY), "pixel_12",40);
		SDL_FRect dstRect = {0,i++*log_interval,0,0};
		SDL_GetTextureSize(texture,&dstRect.w,&dstRect.h);
		SDL_RenderTexture(renderer, texture,nullptr,&dstRect);
	}



}

GameWorld::GameWorld() {
	log_interval = 40;
}

GameWorld::~GameWorld() {
	cout << "GameWorld 已被摧毁!" << endl;
}