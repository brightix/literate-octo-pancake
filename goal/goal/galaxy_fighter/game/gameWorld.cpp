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

void GameWorld::addNewObject(const string& s, shared_ptr<BaseObject> newObject) {
	//if (s == "ground") {
	//	GroundObjects.push_back(newObject);
	//}
	//else if (s == "Bullet") {
	//	BulletObjects.push_back(newObject);
	//}
	//else if (s == "player") {
	//	PlayerObjects.push_back(newObject);
	//}
	objects.push_back(newObject);
}

vector<shared_ptr<BaseObject>>& GameWorld::getObjects() {
	return objects;
}

vector<shared_ptr<BaseObject>>& GameWorld::getGroundObjects() {
	return GroundObjects;
}

//vector<BaseObject*>& GameWorld::getBulletObjects() {
//	return BulletObjects;
//}
//
//vector<BaseObject*>& GameWorld::getPlayerObjects() {
//	return PlayerObjects;
//}


PlayerObject& GameWorld::getPlayer() { return *player; }



GameWorld& GameWorld::Instance() {
	static GameWorld instance;
	return instance;
}

void GameWorld::show_log() {
	Timer& t = Timer::Instance();
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
			cout << "| 玩家坐标x  :" << (short)player->getAttrs()->playerX << ", y:" << (short)player->getAttrs()->playerY << endl;
			cout << "| 玩家状态   :" << player->printActionState() << endl;
		}
		if(camera)
			cout << "| 相机坐标x  :" << (short)camera->getViewport()->x << ", y:" << (short)camera->getViewport()->y << endl;
		cout << "| 分辨率     :" << Resolution::Instance().getWindowRect().w << " x " << Resolution::Instance().getWindowRect().h << endl;
		cout << "+------------------------------------------------" << endl;
		report_log_time = 0;
	}
}

void GameWorld::show_log_on_screen() {
	TextRenderer& textRenderer = TextRenderer::Instance();
	Timer& t = Timer::Instance();
	SDL_Renderer* renderer = RendererManager::Instance().getRenderer();
	SDL_Texture* texture;
	textRenderer.setColor(200,200,200,255);
	int i = 0;
	
	//帧率
	int frameCount = (int)(1 / t.getDeltaTime());
	texture = textRenderer.getTextTexture("帧数:" + to_string(frameCount), "pingfang", 30);
	SDL_FRect dstRect = { 0,i++ * log_interval,0,0 };
	SDL_GetTextureSize(texture, &dstRect.w, &dstRect.h);
	SDL_RenderTexture(renderer, texture, nullptr, &dstRect);
	if (frameCount < Timer::Instance().getCurFrame()*0.9) {
		addError("帧数波动, 出现 " + to_string(frameCount) + "帧");
	}
	//玩家信息
	if (player) {
		auto resolution = Resolution::Instance().getWindowRect();
		texture = textRenderer.getTextTexture("玩家坐标 x:" + to_string((int)player->getAttrs()->playerX) + ", y : " + to_string((int)player->getAttrs()->playerY), "pingfang",30);

		SDL_FRect dstRect = {0,i++*log_interval,0,0};
		SDL_GetTextureSize(texture,&dstRect.w,&dstRect.h);
		SDL_RenderTexture(renderer, texture,nullptr,&dstRect);


		texture = textRenderer.getTextTexture("每秒移速 :" + to_string(player->getVelocityX()), "pingfang", 30);
		dstRect = { 0,i++ * log_interval,0,0 };
		SDL_GetTextureSize(texture, &dstRect.w, &dstRect.h);
		dstRect.x = resolution.w - dstRect.w;
		SDL_RenderTexture(renderer, texture, nullptr, &dstRect);

		texture = textRenderer.getTextTexture("每秒掉落速度 :" + to_string(player->getVelocityY()), "pingfang", 30);
		dstRect = { 0,i++ * log_interval,0,0 };
		SDL_GetTextureSize(texture, &dstRect.w, &dstRect.h);
		dstRect.x = resolution.w - dstRect.w;
		SDL_RenderTexture(renderer, texture, nullptr, &dstRect);
	}
	if (!errorList.empty()) {
		printError();
		errorList.clear();
	}
}

void GameWorld::developmentMode() {

	//玩家碰撞箱
	auto r = RendererManager::Instance().getRenderer();
	for (auto it = objects.begin();it != objects.end();it++) {
		Rect* hitBox = (*it)->getHitBox();
		SDL_SetRenderDrawColor(r, hitBox->color.r, hitBox->color.g, hitBox->color.b, hitBox->color.a);
		SDL_FRect rect = camera->worldToScreen(hitBox->rect);
		SDL_RenderRect(r, &rect);
	}


	//辅助线
	SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
	Resolution& resolution = Resolution::Instance();
	float width = resolution.getWindowRect().w;
	float height = resolution.getWindowRect().h;
	SDL_SetRenderDrawColor(r, 0, 191, 255, 150);
	SDL_RenderLine(r, width/2, 0, width/2, height);//居中垂直线
	SDL_RenderLine(r, 0, height / 2, width, height /2);//居中水平线

	show_log_on_screen();
}

void GameWorld::printError()
{
	cout << "--- errorList ------ * * * " << endl;
	for (string& s : errorList) {
		cout << s << endl;
	}
	cout << "----------------------------------------------------" << endl;
}

void GameWorld::addError(std::string error)
{
	errorList.push_back(error);
}

GameWorld::GameWorld() {
	log_interval = 40;
}

GameWorld::~GameWorld() {
	cout << "GameWorld 已被摧毁!" << endl;
}