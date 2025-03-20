#include "pch.h"
#include "SpritePlayer.h"
#include "../../BehaviorTree/BTAction_player/BTAction_player.h"
#include "../../BehaviorTree/BTAction_player/Action.h"


SpritePlayer::SpritePlayer(PlayerObject* player) : player(player)
{
	//��ʼ������
	this->texture = player->getTexture();
	this->actionFrameDelay = player->getActionFrameDelay();
	
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

	actionState = "NULL";
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
		actionState = tfs;
		elapsed = 0;
		curFrame = (*ss)[actionState].startFrame;
	}
	cout << actionState << endl;
	SpriteSheet& curss = (*ss)[actionState];
	*srcrect = getFrame(curFrame);
	elapsed += Timer::Instance().getDeltaAdjustTime();
	if (elapsed >= (*actionFrameDelay)[curFrame]) {
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
	auto state = player->getActionState();

	if ((*state)["isAttack"]) {
		return "Attack";
	}
	else if ((*state)["Idle_to_Jump"]) {
		return "Idle_to_Jump";
	}
	else if ((*state)["isJump"]) {
		return "Jump";
	}
	else if ((*state)["Jump_to_Fall"]) {
		return "Jump_to_Fall";
	}
	else if ((*state)["isFall"]) {
		return "Fall";
	}
	else if ((*state)["Fall_to_Idle"]) {
		return "Fall_to_Idle";
	}
	else if ((*state)["Idle_to_Down"]) {
		return "Idle_to_Down";
	}
	else if ((*state)["Down"]) {
		return "Down";
	}
	else if ((*state)["Down_to_Idle"]) {
		return "Down_to_Idle";
	}
	else if ((*state)["Idle_to_Run"]) {
		return "Idle_to_Run";
	}
	else if ((*state)["isRun"]) {
		return "Run";
	}
	else if ((*state)["Run_to_Idle"]) {
		return "Run_to_Idle";
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
