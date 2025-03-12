#include "pch.h"
#include "SpritePlayer.h"
#include "../../BehaviorTree/BTAction_player/BTAction_player.h"

SpritePlayer::SpritePlayer(
	SDL_Texture* texture,
	SDL_FRect* viewport,
	std::unordered_map<PlayerState,SpriteSheet>* spriteSheet,
	std::unordered_map<PlayerState, double>* actionFrameDelay,
	PlayerState* playerState,
	float frameWidth,
	float frameHeight,
	int framesCount)
{
	//��ʼ������
	this->texture = texture;
	this->viewportRect = viewport;
	this->spriteSheet = spriteSheet;
	this->actionFrameDelay = actionFrameDelay;
	this->localState = PlayerState::Idle;
	this->playerState = playerState;
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
	this->framesCount = framesCount;


	//��ʼ������
	this->root = make_unique<ParalleNode>();

	float textureWidth, textureHeight;
	SDL_GetTextureSize(texture,&textureWidth,&textureHeight);
	for (int row = 0;row * frameHeight < textureHeight;row++) {
		for (int col = 0;col*frameWidth < textureWidth;col++) {
			frames.push_back({frameWidth * col,frameHeight * row,frameWidth,frameHeight});//ˮƽ���еľ����
		}
	}

	this->spriteFrameRect = { 1,1,frameWidth,frameHeight };
	initAction();
	root->addChild(make_unique<BTAction_player::display_anime_at_center>(texture,spriteFrameRect,viewportRect,0.0));
}





bool SpritePlayer::update() {				//����update
	setSpriteFrameRect(playerState,elapsed);
	return root->execute();
}

void SpritePlayer::setSpriteFrameRect(PlayerState* state, float elapsed) {//���þ��鵱ǰ֡����
	if (localState != *state) {//���ֶ����任
		localState = *state;
		initAction();
	}
	//���Ӿ���ʱ�䣬�ж��Ƿ������һ֡��ѭ��
	refreshTime();
	auto idx = elapsed / (*actionFrameDelay)[localState];
	SpriteSheet& t = (*spriteSheet)[localState];

	SDL_FRect& newFrame = getFrame(((int)idx - t.startFrame) % (t.endFrame - t.startFrame));
	spriteFrameRect.x = newFrame.x;
	spriteFrameRect.y = newFrame.y;
}

void SpritePlayer::initAction() {			//���������仯������ʱ��
	elapsed = 0;
}

void SpritePlayer::refreshTime() {			//ˢ��ʱ��
	elapsed += Timer::getInstance().getDeltaAdjustTime();
}

SDL_FRect& SpritePlayer::getFrame(int idx) {//��ȡ��ǰ֡
	return frames[idx];
}




SDL_Texture* SpritePlayer::getTexture() {	//��������
	return texture;
}

