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

	
	short curAction;//��ͬ�� PlayerState


	void refreshTime();
	void initAction();
public:
	//��ʼ��
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
	
	//��ȡʱ��֡
	SDL_FRect& getFrame(int idx);
	
	//��ȡ�����
	SDL_Texture* getTexture();

};

