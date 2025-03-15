#include "pch.h"
#include "gameWorld.h"

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



GameWorld::~GameWorld() {
	cout << "GameWorld 已被摧毁!" << endl;
}