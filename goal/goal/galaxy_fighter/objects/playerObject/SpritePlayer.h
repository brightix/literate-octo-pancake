#pragma once
#include "pch.h"
#include "PlayerObject.h"
#include "../../BehaviorTree/paralle/ParalleNode.h"
#include "../../core/Context.h"

typedef struct SpriteSheet {
	int startFrame;//��ʼ֡
	int pre;//ǰҡ֡��
	int running;//����֡��
	int post;//��ҡ֡��
	int endFrame;//����֡
	bool isLoop;//�Ƿ�ѭ������
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
	//��ʼ��
	SpritePlayer(std::shared_ptr<Context> context);

	void setSpriteFrameRect(PlayerState* state, float& elapsed);



	bool update();
	
	//��ȡʱ��֡
	SDL_FRect& getFrame(int idx);


	
	//��ȡ�����
	SDL_Texture* getTexture();

	bool isAnimationFinished();

};

