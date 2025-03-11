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
	short curAction;//��ͬ�� PlayerState


	void refreshTime();
	void initAction();
public:
	//��ֹ���ִ��಻����Ĭ�Ϲ��캯��
	SpritePlayer() = default;
	
	//��ʼ��
	SpritePlayer(SDL_Texture* texture, SDL_FRect* viewport, PlayerState playerState,int frameWidth,int frameHeight,int framesCount);

	void setSpriteFrameRect(PlayerState state, float elapsed);



	bool update();
	
	//��ȡʱ��֡
	SDL_FRect& getFrame(int idx);
	
	//��ȡ�����
	SDL_Texture* getTexture();

};

