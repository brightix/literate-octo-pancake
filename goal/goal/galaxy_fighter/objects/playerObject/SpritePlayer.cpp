#include "pch.h"
#include "SpritePlayer.h"
#include "../../BehaviorTree/BTAction_player/BTAction_player.h"

SpritePlayer::SpritePlayer(std::shared_ptr<Context> context) : context(context)
{
	//��ʼ������
	this->texture = context->getData<SDL_Texture>("texture").get();
	this->viewportRect = context->getData<SDL_FRect>("rect").get();
	this->spriteSheet = context->getData<unordered_map<PlayerState,SpriteSheet>>("spriteSheet").get();
	this->actionFrameDelay = context->getData<unordered_map<PlayerState, double>>("actionFrameDelay").get();;
	this->localState = PlayerState::Idle;

	//��ʼ������
	this->root = make_unique<ParalleNode>();

	float textureWidth, textureHeight;//���Ŵ�С
	SDL_GetTextureSize(texture, &textureWidth, &textureHeight);


	float frameWidth = context->getData<PlayerAttrs>("playerAttrs")->player_sprite_frame_width;
	float frameHeight = context->getData<PlayerAttrs>("playerAttrs")->player_sprite_frame_height;//��֡��С

	for (int row = 0;row * frameHeight < textureHeight;row++) {
		for (int col = 0;col*frameWidth < textureWidth;col++) {
			frames.push_back({frameWidth * col,frameHeight * row, frameWidth,frameHeight});//ˮƽ���еľ����
		}
	}

	this->spriteFrameRect = { 1,1,frameWidth,frameHeight };
	initAction();
	root->addChild(make_unique<BTAction_player::display_anime_at_center>(texture,spriteFrameRect,viewportRect,0.0,&context->getData<PlayerAttrs>("playerAttrs")->player_orientation));
}





bool SpritePlayer::update() {				//����update
	setSpriteFrameRect(context->getData<PlayerState>("playerState").get(), elapsed);
	return root->execute();
}

void SpritePlayer::setSpriteFrameRect(PlayerState* state, float elapsed) {//���þ��鵱ǰ֡����
	if (localState != *state) {//���ֶ����任
		localState = *state;
		initAction();
	}
	//���Ӿ���ʱ�䣬�ж��Ƿ������һ֡��ѭ��
	refreshTime();
	//���ֽṹ

	//����ֹͣ
	if (localState == PlayerState::Down) {

	}


	//ѭ������
	else if (localState == PlayerState::Left || localState == PlayerState::Right) {
		int idx = elapsed / (*actionFrameDelay)[localState];
		SpriteSheet& t = (*spriteSheet)[localState];
		SDL_FRect& newFrame = getFrame(idx % (t.endFrame - t.startFrame) + t.startFrame);
		spriteFrameRect.x = newFrame.x;
		spriteFrameRect.y = newFrame.y;
	}

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

