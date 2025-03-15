#pragma once
#include "pch.h"
#include "PlayerObject.h"
#include "../../BehaviorTree/paralle/ParalleNode.h"
#include "../../core/Context.h"

typedef struct SpriteSheet {
	int startFrame;//开始帧
	int pre;//前摇帧数
	int running;//运行帧数
	int post;//后摇帧数
	int endFrame;//结束帧
	bool isLoop;//是否循环播放
}SpriteSheet;


enum AnimeState {
	pre,running,post,none
};
class SpritePlayer
	{
		std::shared_ptr<Context> context;
		SDL_Texture* texture;
		SDL_FRect* viewportRect;
		std::unordered_map<PlayerState, SpriteSheet>* spriteSheet;
		std::shared_ptr<std::vector<float>> actionFrameDelay;
		PlayerState* playerState;
		PlayerState localState;


		std::vector<SDL_FRect> frames;
		SDL_FRect spriteFrameRect;
	
		int textureWidth;	
		float elapsed;
		short curFrame;
		AnimeState animeState;

	
	
	std::unique_ptr<ParalleNode> root;

	


	void updateFrame();
	void refreshTime();
	void initAction();
public:
	//初始化
	SpritePlayer(std::shared_ptr<Context> context);

	void setSpriteFrameRect(PlayerState* state, float& elapsed);



	bool update();
	
	//获取时间帧
	SDL_FRect& getFrame(int idx);


	
	//获取精灵表
	SDL_Texture* getTexture();

	bool isAnimationFinished();

};

