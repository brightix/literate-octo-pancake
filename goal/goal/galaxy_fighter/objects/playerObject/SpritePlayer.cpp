#include "pch.h"
#include "SpritePlayer.h"
#include "../../BehaviorTree/BTAction_player/BTAction_player.h"

SpritePlayer::SpritePlayer(SDL_Texture* texture,SDL_FRect* viewport, PlayerState playerState,int frameWidth, int frameHeight, int framesCount)
{

	//��ʼ������
	this->localState = PlayerState::Idle;
	this->playerState = playerState;
	this->texture = texture;

	this->viewportRect = viewport;
	
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
	this->framesCount = framesCount;
	this->root = make_unique<ParalleNode>();
	this->ActionFrameDelay = {	
								{ static_cast<short>(PlayerState::Idle),50 },
								{ static_cast<short>(PlayerState::Jump),100 },
								{ static_cast<short>(PlayerState::Down),100 },
								{ static_cast<short>(PlayerState::Left),100 },
								{ static_cast<short>(PlayerState::Right),100 },
								{ static_cast<short>(PlayerState::Left | PlayerState::Jump),100 },
								{ static_cast<short>(PlayerState::Right | PlayerState::Jump),100 }
	};

	//��ʼ������
	for (int i = 0;i < framesCount;i++) {
		frames.push_back({ 0,(float)frameHeight * i ,(float)frameWidth,(float)frameHeight });//��ֱ���еľ����
	}


	this->spriteFrameRect = &getFrame(0);
	setSpriteFrameRect(PlayerState::Idle,0.0);
	initAction();
	root->addChild(make_unique<BTAction_player::display_anime_at_center>(texture,spriteFrameRect,viewportRect,0.0));
}





bool SpritePlayer::update() {				//����update
	
	setSpriteFrameRect(playerState,elapsed);

	root->execute();
	return true;
}

void SpritePlayer::setSpriteFrameRect(PlayerState state, float elapsed) {//���þ��鵱ǰ֡����

	if (localState != state) {//���ֶ����任
		localState = state;
		initAction();
	}
	//���Ӿ���ʱ�䣬�ж��Ƿ������һ֡��ѭ��
	refreshTime();
	*spriteFrameRect = getFrame((int)(elapsed / ActionFrameDelay[curAction]) % framesCount);
}

void SpritePlayer::initAction() {			//���������仯������ʱ��
	elapsed = -Timer::getInstance().getDeltaAdjustTime();
}

void SpritePlayer::refreshTime() {			//ˢ��ʱ��
	elapsed += Timer::getInstance().getDeltaAdjustTime();
}

SDL_FRect& SpritePlayer::getFrame(int idx) {//��ȡ��ǰ֡
	cout << "��ǰ֡��  " << idx << endl;
	return frames[idx];
}




SDL_Texture* SpritePlayer::getTexture() {	//��������
	return texture;
}

