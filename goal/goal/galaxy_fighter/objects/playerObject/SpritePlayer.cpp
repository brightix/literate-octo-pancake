#include "pch.h"
#include "SpritePlayer.h"
#include "../../BehaviorTree/BTAction_player/BTAction_player.h"
#include "../../BehaviorTree/BTAction_player/Action.h"


SpritePlayer::SpritePlayer(PlayerObject* player) : player(player)
{
	//��ʼ������
	this->texture = player->getTexture();
	//this->actionFrameDelay = player->getActionFrameDelay();
	
	//��ʼ������
	this->root = make_unique<ParalleNode>();

	float textureWidth, textureHeight;//���Ŵ�С
	SDL_GetTextureSize(texture.get(), &textureWidth, &textureHeight);
	attrs = player->getAttrs();

	float frameWidth = attrs->player_sprite_frame_width;
	float frameHeight = attrs->player_sprite_frame_height;//��֡��С

	for (int row = 0;row * frameHeight < textureHeight;row++) {
		for (int col = 0;col*frameWidth < textureWidth;col++) {
			frames.push_back({frameWidth * col,frameHeight * row, frameWidth,frameHeight});//ˮƽ���еľ����
		}
	}

	srcrect = make_shared<SDL_FRect>(SDL_FRect({ 1,1,frameWidth,frameHeight }));
	nextAction = "NONE";
	actionState = "Idle";
	angle = 0.0;
	root->addChild(make_shared<display_at_position>(texture, srcrect, player->getRenderRect(), &angle, &attrs->player_orientation));
}


bool SpritePlayer::update() {				//����update
	setSpriteFrameRect();
	return root->execute();
}

void SpritePlayer::setSpriteFrameRect() {
	auto state = player->getActionState();
	auto ss = player->getSpriteSheet();
	string tfs = TransFormState();
	if (actionState != tfs) {
		if (nextAction != "NONE") {
			actionState = nextAction;
			nextAction = "NONE";
			curFrame = (*ss)[actionState].startFrame;
			elapsed = 0;
			cout << "ִ����Ԥ����" << endl;
		}
		else if ((*ss)[actionState].isInterruptible) {
			actionState = tfs;
			elapsed = 0;
			curFrame = (*ss)[actionState].startFrame;
		}
		else if ((*ss)[actionState].endFrame - curFrame <= 3) {
			nextAction = tfs;
		}
	}

	SpriteSheet& curss = (*ss)[actionState];
	*srcrect = getFrame(curFrame);
	elapsed += Timer::Instance().getDeltaAdjustTime();
	if (elapsed >= (*ss)[actionState].actionDelay) {
		//cout << curFrame << endl;
		cout << actionState << endl;
		if (++curFrame >= curss.endFrame) {
			if (curss.isLoop) {
				curFrame = curss.startFrame;
			}
			else {
				(*state)[actionState] = false;
			}
		}
		elapsed = 0;
	}
}

string SpritePlayer::TransFormState() {
	auto actionPriority = *player->getActionPriority();
	auto state = player->getActionState();
	for (auto action : actionPriority)
	{
		if ((*state)[action]) return action;
	}
	return "Idle";
}

SDL_FRect& SpritePlayer::getFrame(int idx) {//��ȡ��ǰ֡
	return frames[idx];
}

//void SpritePlayer::initAction() {
//	curFrame = (*spriteSheet)[localState].startFrame;
//	animeState = pre;
//}
//
//void SpritePlayer::refreshTime() {			//ˢ��ʱ��
//	elapsed += Timer::Instance().getDeltaAdjustTime();
//}
//

//
//void SpritePlayer::updateFrame() {//��ȡ��ǰ֡
//	//cout << curFrame << endl;
//	if (curFrame > frames.size()) {
//		cerr << "�������Խ�磬���ֵ��" << frames.size() << "��ǰֵ" << curFrame<< endl;
//		curFrame = 0;
//	}
//	spriteFrameRect.x = frames[curFrame].x;
//	spriteFrameRect.y = frames[curFrame].y;
//}
//
//
//
//
//SDL_Texture* SpritePlayer::getTexture() {	//��������
//	return texture;
//}
//
//bool SpritePlayer::isAnimationFinished() {
//	return animeState == none || isAnyStateNonInterruptible(localState);
//}
//
//
//��Ҷ�������
