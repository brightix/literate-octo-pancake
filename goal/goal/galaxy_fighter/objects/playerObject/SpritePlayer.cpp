#include "pch.h"
#include "SpritePlayer.h"
#include "../../BehaviorTree/BTAction_player/BTAction_player.h"

SpritePlayer::SpritePlayer(std::shared_ptr<Context> context) : context(context)
{
	//��ʼ������
	this->texture = context->getData<SDL_Texture>("texture").get();
	this->viewportRect = context->getData<SDL_FRect>("rect").get();
	this->spriteSheet = context->getData<unordered_map<PlayerState,SpriteSheet>>("spriteSheet").get();
	this->actionFrameDelay = context->getData<vector<float>>("actionFrameDelay");
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
	this->curFrame = 0;
	initAction();
	root->addChild(make_unique<BTAction_player::display_anime_at_center>(texture,spriteFrameRect,viewportRect,0.0,&context->getData<PlayerAttrs>("playerAttrs")->player_orientation));
}





bool SpritePlayer::update() {				//����update
	setSpriteFrameRect(context->getData<PlayerState>("playerState").get(), elapsed);
	return root->execute();
}

void SpritePlayer::setSpriteFrameRect(PlayerState* state, float& elapsed) {//���þ��鵱ǰ֡����
	if (*state != PlayerState::Idle && localState != *state) {//���ֶ����任
		localState = *state;
		initAction();
	}
	//if(context->getData<bool>("is"))
	//���Ӿ���ʱ�䣬�ж��Ƿ������һ֡��ѭ��
	refreshTime();
	if (animeState == pre && (*spriteSheet)[localState].isLoop) animeState = running;
	int idx;
	int preFrameEnd = (*spriteSheet)[localState].startFrame + (*spriteSheet)[localState].pre;
	int runningFrameEnd = (*spriteSheet)[localState].startFrame + (*spriteSheet)[localState].running;
	int postFrameEnd = (*spriteSheet)[localState].startFrame + (*spriteSheet)[localState].endFrame;
	switch (animeState) {
	case pre:
		updateFrame();
		if (elapsed >= (*actionFrameDelay)[curFrame]) {
			if (++curFrame > preFrameEnd) {
				animeState = running;
			}
			elapsed = 0;
		}
		break;
	case running:
		updateFrame();
		if (elapsed >= (*actionFrameDelay)[curFrame]) {
			if (++curFrame >= runningFrameEnd) {
				if ((*spriteSheet)[localState].isLoop) {
					curFrame = preFrameEnd;
				}
				else {
					animeState = post;
				}
			}
			elapsed = 0;
		}
		break;
	case post:
		updateFrame();
		if (elapsed >= (*actionFrameDelay)[curFrame]) {
			if (++curFrame >= postFrameEnd) {
				animeState = pre;
				//context->setData("playerState", PlayerState::Idle);
			}
			elapsed = 0;
		}
		break;
	case none:
		//cout << "��ɫ��״̬" << endl;
		break;
	default:
		cerr << "animeState����,animeState������ " << animeState << "��ֵ" << endl;
	}
}

void SpritePlayer::initAction() {
	curFrame = (*spriteSheet)[localState].startFrame;
	animeState = pre;
}

void SpritePlayer::refreshTime() {			//ˢ��ʱ��
	elapsed += Timer::getInstance().getDeltaAdjustTime();
}

SDL_FRect& SpritePlayer::getFrame(int idx) {//��ȡ��ǰ֡
	return frames[idx];
}

void SpritePlayer::updateFrame() {//��ȡ��ǰ֡
	//cout << curFrame << endl;
	spriteFrameRect.x = frames[curFrame].x;
	spriteFrameRect.y = frames[curFrame].y;
}




SDL_Texture* SpritePlayer::getTexture() {	//��������
	return texture;
}

bool SpritePlayer::isAnimationFinished() {
	return animeState == none || (*spriteSheet)[localState].isLoop;
}