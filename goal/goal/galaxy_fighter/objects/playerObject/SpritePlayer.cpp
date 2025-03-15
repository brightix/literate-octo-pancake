#include "pch.h"
#include "SpritePlayer.h"
#include "../../BehaviorTree/BTAction_player/BTAction_player.h"

SpritePlayer::SpritePlayer(std::shared_ptr<Context> context) : context(context)
{
	//初始化属性
	this->texture = context->getData<SDL_Texture>("texture").get();
	this->viewportRect = context->getData<SDL_FRect>("rect").get();
	this->spriteSheet = context->getData<unordered_map<PlayerState,SpriteSheet>>("spriteSheet").get();
	this->actionFrameDelay = context->getData<unordered_map<PlayerState, double>>("actionFrameDelay").get();;
	this->localState = PlayerState::Idle;

	//初始化调用
	this->root = make_unique<ParalleNode>();

	float textureWidth, textureHeight;//整张大小
	SDL_GetTextureSize(texture, &textureWidth, &textureHeight);


	float frameWidth = context->getData<PlayerAttrs>("playerAttrs")->player_sprite_frame_width;
	float frameHeight = context->getData<PlayerAttrs>("playerAttrs")->player_sprite_frame_height;//单帧大小

	for (int row = 0;row * frameHeight < textureHeight;row++) {
		for (int col = 0;col*frameWidth < textureWidth;col++) {
			frames.push_back({frameWidth * col,frameHeight * row, frameWidth,frameHeight});//水平排列的精灵表
		}
	}

	this->spriteFrameRect = { 1,1,frameWidth,frameHeight };
	initAction();
	root->addChild(make_unique<BTAction_player::display_anime_at_center>(texture,spriteFrameRect,viewportRect,0.0,&context->getData<PlayerAttrs>("playerAttrs")->player_orientation));
}





bool SpritePlayer::update() {				//就是update
	setSpriteFrameRect(context->getData<PlayerState>("playerState").get(), elapsed);
	return root->execute();
}

void SpritePlayer::setSpriteFrameRect(PlayerState* state, float elapsed) {//设置精灵当前帧矩形
	if (localState != *state) {//出现动作变换
		localState = *state;
		initAction();
	}
	//增加经过时间，判断是否可以下一帧或循环
	refreshTime();
	//两种结构

	//播完停止
	if (localState == PlayerState::Down) {

	}


	//循环播放
	else if (localState == PlayerState::Left || localState == PlayerState::Right) {
		int idx = elapsed / (*actionFrameDelay)[localState];
		SpriteSheet& t = (*spriteSheet)[localState];
		SDL_FRect& newFrame = getFrame(idx % (t.endFrame - t.startFrame) + t.startFrame);
		spriteFrameRect.x = newFrame.x;
		spriteFrameRect.y = newFrame.y;
	}

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

