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
	//初始化属性
	this->texture = texture;
	this->viewportRect = viewport;
	this->spriteSheet = spriteSheet;
	this->actionFrameDelay = actionFrameDelay;
	this->localState = PlayerState::Idle;
	this->playerState = playerState;
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
	this->framesCount = framesCount;


	//初始化调用
	this->root = make_unique<ParalleNode>();

	float textureWidth, textureHeight;
	SDL_GetTextureSize(texture,&textureWidth,&textureHeight);
	for (int row = 0;row * frameHeight < textureHeight;row++) {
		for (int col = 0;col*frameWidth < textureWidth;col++) {
			frames.push_back({frameWidth * col,frameHeight * row,frameWidth,frameHeight});//水平排列的精灵表
		}
	}

	this->spriteFrameRect = { 1,1,frameWidth,frameHeight };
	initAction();
	root->addChild(make_unique<BTAction_player::display_anime_at_center>(texture,spriteFrameRect,viewportRect,0.0));
}





bool SpritePlayer::update() {				//就是update
	setSpriteFrameRect(playerState,elapsed);
	return root->execute();
}

void SpritePlayer::setSpriteFrameRect(PlayerState* state, float elapsed) {//设置精灵当前帧矩形
	if (localState != *state) {//出现动作变换
		localState = *state;
		initAction();
	}
	//增加经过时间，判断是否可以下一帧或循环
	refreshTime();
	auto idx = elapsed / (*actionFrameDelay)[localState];
	SpriteSheet& t = (*spriteSheet)[localState];

	SDL_FRect& newFrame = getFrame(((int)idx - t.startFrame) % (t.endFrame - t.startFrame));
	spriteFrameRect.x = newFrame.x;
	spriteFrameRect.y = newFrame.y;
}

void SpritePlayer::initAction() {			//遇到动作变化就重置时间
	elapsed = 0;
}

void SpritePlayer::refreshTime() {			//刷新时间
	elapsed += Timer::getInstance().getDeltaAdjustTime();
}

SDL_FRect& SpritePlayer::getFrame(int idx) {//获取当前帧
	return frames[idx];
}




SDL_Texture* SpritePlayer::getTexture() {	//返回纹理
	return texture;
}

