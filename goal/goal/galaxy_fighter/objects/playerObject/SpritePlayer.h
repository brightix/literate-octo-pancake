#pragma once
#include "pch.h"
#include "PlayerObject.h"
#include "../../BehaviorTree/paralle/ParalleNode.h"

typedef struct SpriteSheet {
	int startFrame;
	int endFrame;
}SpriteSheet;

	class SpritePlayer
	{
		SDL_Texture* texture;
		SDL_FRect* viewportRect;
		std::unordered_map<PlayerState, SpriteSheet>* spriteSheet;
		std::unordered_map<PlayerState, double>* actionFrameDelay;
		PlayerState* playerState;
		PlayerState localState;


		std::vector<SDL_FRect> frames;
		SDL_FRect spriteFrameRect;
	
		int textureWidth;
		int frameWidth, frameHeight, framesCount;
		float elapsed;



	
	
	std::unique_ptr<ParalleNode> root;

	
	short curAction;//等同于 PlayerState


	void refreshTime();
	void initAction();
public:
	//初始化
	SpritePlayer(
		SDL_Texture* texture,
		SDL_FRect* viewport,
		std::unordered_map<PlayerState, SpriteSheet>* spriteSheet,
		std::unordered_map<PlayerState, double>* actionFrameDelay,
		PlayerState* playerState,
		float frameWidth,
		float frameHeight,
		int framesCount);

	void setSpriteFrameRect(PlayerState* state, float elapsed);



	bool update();
	
	//获取时间帧
	SDL_FRect& getFrame(int idx);
	
	//获取精灵表
	SDL_Texture* getTexture();

};

