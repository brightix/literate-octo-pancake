#include "pch.h"
#include "SpritePlayer.h"
#include "../../BehaviorTree/BTAction_player/BTAction_player.h"

SpritePlayer::SpritePlayer(SDL_Texture* texture,SDL_FRect* viewport, PlayerState playerState,int frameWidth, int frameHeight, int framesCount)
{

	//初始化属性
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

	//初始化调用
	for (int i = 0;i < framesCount;i++) {
		frames.push_back({ 0,(float)frameHeight * i ,(float)frameWidth,(float)frameHeight });//垂直排列的精灵表
	}


	this->spriteFrameRect = &getFrame(0);
	setSpriteFrameRect(PlayerState::Idle,0.0);
	initAction();
	root->addChild(make_unique<BTAction_player::display_anime_at_center>(texture,spriteFrameRect,viewportRect,0.0));
}





bool SpritePlayer::update() {				//就是update
	
	setSpriteFrameRect(playerState,elapsed);

	root->execute();
	return true;
}

void SpritePlayer::setSpriteFrameRect(PlayerState state, float elapsed) {//设置精灵当前帧矩形

	if (localState != state) {//出现动作变换
		localState = state;
		initAction();
	}
	//增加经过时间，判断是否可以下一帧或循环
	refreshTime();
	*spriteFrameRect = getFrame((int)(elapsed / ActionFrameDelay[curAction]) % framesCount);
}

void SpritePlayer::initAction() {			//遇到动作变化就重置时间
	elapsed = -Timer::getInstance().getDeltaAdjustTime();
}

void SpritePlayer::refreshTime() {			//刷新时间
	elapsed += Timer::getInstance().getDeltaAdjustTime();
}

SDL_FRect& SpritePlayer::getFrame(int idx) {//获取当前帧
	cout << "当前帧：  " << idx << endl;
	return frames[idx];
}




SDL_Texture* SpritePlayer::getTexture() {	//返回纹理
	return texture;
}

