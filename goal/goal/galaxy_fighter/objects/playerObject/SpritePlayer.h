#pragma once
#include "pch.h"
#include "PlayerObject.h"
#include "../../BehaviorTree/paralle/ParalleNode.h"
class SpritePlayer
{
	SDL_Texture* texture;
	std::vector<SDL_FRect> frames;
	SDL_FRect* spriteFrameRect;
	SDL_FRect* viewportRect;
	int textureWidth;
	int frameWidth, frameHeight, framesCount;
	float elapsed;



	PlayerState playerState;
	PlayerState localState;
	std::unique_ptr<ParalleNode> root;

	std::unordered_map<short, double> ActionFrameDelay;
	short curAction;//等同于 PlayerState


	void refreshTime();
	void initAction();
public:
	//防止出现此类不存在默认构造函数
	SpritePlayer() = default;
	
	//初始化
	SpritePlayer(SDL_Texture* texture, SDL_FRect* viewport, PlayerState playerState,int frameWidth,int frameHeight,int framesCount);

	void setSpriteFrameRect(PlayerState state, float elapsed);



	bool update();
	
	//获取时间帧
	SDL_FRect& getFrame(int idx);
	
	//获取精灵表
	SDL_Texture* getTexture();

};

