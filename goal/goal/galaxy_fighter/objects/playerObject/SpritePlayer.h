#pragma once
#include "pch.h"
#include "PlayerObject.h"
#include "../../BehaviorTree/paralle/ParalleNode.h"
#include "../../core/Context.h"

typedef struct SpriteSheet {
	int startFrame;
	int endFrame;
}SpriteSheet;

	class SpritePlayer
	{
		std::shared_ptr<Context> context;
		SDL_Texture* texture;
		SDL_FRect* viewportRect;
		std::unordered_map<PlayerState, SpriteSheet>* spriteSheet;
		std::unordered_map<PlayerState, double>* actionFrameDelay;
		PlayerState* playerState;
		PlayerState localState;


		std::vector<SDL_FRect> frames;
		SDL_FRect spriteFrameRect;
	
		int textureWidth;
		float elapsed;



	
	
	std::unique_ptr<ParalleNode> root;

	
	short curAction;//��ͬ�� PlayerState


	void refreshTime();
	void initAction();
public:
	//��ʼ��
	SpritePlayer(std::shared_ptr<Context> context);

	void setSpriteFrameRect(PlayerState* state, float elapsed);



	bool update();
	
	//��ȡʱ��֡
	SDL_FRect& getFrame(int idx);
	
	//��ȡ�����
	SDL_Texture* getTexture();

};

