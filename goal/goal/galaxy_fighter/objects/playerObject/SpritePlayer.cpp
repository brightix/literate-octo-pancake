#include "pch.h"
#include "SpritePlayer.h"
#include "../../BehaviorTree/BTAction_player/BTAction_player.h"

SpritePlayer::SpritePlayer(std::shared_ptr<Context> context) : context(context)
{
	//初始化属性
	this->texture = context->getData<SDL_Texture>("texture").get();
	this->viewportRect = context->getData<SDL_FRect>("rect").get();
	this->spriteSheet = context->getData<unordered_map<PlayerState,SpriteSheet>>("spriteSheet").get();
	this->actionFrameDelay = context->getData<vector<float>>("actionFrameDelay");
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
	this->curFrame = 0;
	initAction();
	root->addChild(make_unique<BTAction_player::display_anime_at_center>(texture,spriteFrameRect,viewportRect,0.0,&context->getData<PlayerAttrs>("playerAttrs")->player_orientation));
}





bool SpritePlayer::update() {				//就是update
	setSpriteFrameRect(context->getData<PlayerState>("playerState").get(), elapsed);
	return root->execute();
}

void SpritePlayer::setSpriteFrameRect(PlayerState* state, float& elapsed) {//设置精灵当前帧矩形
	if (*state != PlayerState::Idle && localState != *state) {//出现动作变换
		localState = *state;
		initAction();
	}
	//if(context->getData<bool>("is"))
	//增加经过时间，判断是否可以下一帧或循环
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
		//cout << "角色无状态" << endl;
		break;
	default:
		cerr << "animeState出错,animeState被给予 " << animeState << "数值" << endl;
	}
}

void SpritePlayer::initAction() {
	curFrame = (*spriteSheet)[localState].startFrame;
	animeState = pre;
}

void SpritePlayer::refreshTime() {			//刷新时间
	elapsed += Timer::getInstance().getDeltaAdjustTime();
}

SDL_FRect& SpritePlayer::getFrame(int idx) {//获取当前帧
	return frames[idx];
}

void SpritePlayer::updateFrame() {//获取当前帧
	//cout << curFrame << endl;
	spriteFrameRect.x = frames[curFrame].x;
	spriteFrameRect.y = frames[curFrame].y;
}




SDL_Texture* SpritePlayer::getTexture() {	//返回纹理
	return texture;
}

bool SpritePlayer::isAnimationFinished() {
	return animeState == none || (*spriteSheet)[localState].isLoop;
}