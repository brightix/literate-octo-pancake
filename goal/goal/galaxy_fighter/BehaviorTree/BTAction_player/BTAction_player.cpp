#include "pch.h"
#include "BTAction_player.h"

using namespace BTAction_player;

//display_at_position::display_at_position(SDL_Texture* texture, SDL_FRect* rect, double angle) {
//	this->texture = texture;
//	this->rect = rect;
//	this->angle = angle;
//}

//bool display_at_position::execute() {
//	
//	if (SDL_RenderTextureRotated(RendererManager::getInstance().getRenderer(), texture, nullptr, rect, angle, nullptr, SDL_FLIP_NONE)) {
//		return true;
//	}
//	else {
//		SDL_Log("渲染纹理失败");
//		return false;
//	}
//}


display_at_center::display_at_center(SDL_Texture* texture,SDL_FRect* parentRect,double angle)
{
	Camera& camera = Camera::getInstance();
	windowRect = &Resolution::getInstance().getWindowRect();
	rect_show = {0,0,parentRect->w,parentRect->h};
	this->parentRect = parentRect;
	this->texture = texture;
	this->angle = angle;
}

bool display_at_center::execute()
{
	auto isCrashed = Camera::getInstance().ownerxyCrashedState();
	if (isCrashed.first) {
		rect_show.x = parentRect->x - Camera::getInstance().getViewport()->x;
	}
	else rect_show.x = windowRect->w / 2 - parentRect->w / 2;
	if(isCrashed.second){
		rect_show.y = parentRect->y - Camera::getInstance().getViewport()->y;
	}
	else rect_show.y = windowRect->h / 2 - parentRect->h / 2;
	if (SDL_RenderTextureRotated(RendererManager::getInstance().getRenderer(), texture, nullptr, &rect_show, angle, nullptr, SDL_FLIP_NONE)) {
		return true;
	}
	else {
		SDL_Log("渲染纹理失败");
		return false;
	}
}


display_anime_at_center::display_anime_at_center(SDL_Texture* texture, SDL_FRect& spriteFrameRect,SDL_FRect* parentRect, double angle,bool* isTowardRight) : spriteFrameRect(spriteFrameRect)
{
	Camera& camera = Camera::getInstance();	
	windowRect = &Resolution::getInstance().getWindowRect();
	rect_show = { 0,0,parentRect->w,parentRect->h };
	this->parentRect = parentRect;
	this->texture = texture;
	this->angle = angle;
	this->spriteFrameRect = spriteFrameRect;
	this->isTowardRight = isTowardRight;
}

bool display_anime_at_center::execute() {
	auto isCrashed = Camera::getInstance().ownerxyCrashedState();
	if (isCrashed.first) {
		rect_show.x = parentRect->x - Camera::getInstance().getViewport()->x;
	} else {
		rect_show.x = windowRect->w / 2 - parentRect->w / 2;
	} 
	if (isCrashed.second) {
		rect_show.y = parentRect->y - Camera::getInstance().getViewport()->y;
	} else {
		rect_show.y = windowRect->h / 2 - parentRect->h / 2;
	}
	if (SDL_RenderTextureRotated(RendererManager::getInstance().getRenderer(), texture, &spriteFrameRect, &rect_show, angle, nullptr, (*isTowardRight) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL)) {
		return true;
	} else {
		SDL_Log("渲染纹理失败");
		return false;
	}
}




player_move_image::player_move_image(shared_ptr<Context> context) : BTNode(context){

}

bool player_move_image::execute() {
	float dx = 0, dy = 0;
	PlayerAttrs* attrs = getter()->getData<PlayerAttrs>("playerAttrs").get();
	
	const bool* keystate = SDL_GetKeyboardState(nullptr);
	if (keystate[SDL_SCANCODE_UP]) dy -= 1;
	if (keystate[SDL_SCANCODE_LEFT]) dx -= 1;
	if (keystate[SDL_SCANCODE_DOWN]) dy += 1;
	if (keystate[SDL_SCANCODE_RIGHT]) dx += 1;
	
	float length = std::sqrt(dy*dy + dx*dx);

	if (length > 0) {
		dx /= length;
		dy /= length;
		//getter()->getData<PlayerObject>("this")->removePlayerState(PlayerState::Idle);
	}
	else {
		//getter()->getData<PlayerObject>("this")->setPlayerState(PlayerState::Idle);
		return false;
	}
	//auto move_speed = attrs->player_move_speed;
	//auto [limit_w, limit_h] = Camera::getInstance().getCameraRange();
	//attrs->playerX += move_speed * dx;
	//attrs->playerY += move_speed * dy;
	//attrs->playerX = clamp(attrs->playerX, 0.0f, limit_w - getter()->getData<SDL_FRect>("rect")->w);
	//attrs->playerY = clamp(attrs->playerY, 0.0f, limit_h - getter()->getData<SDL_FRect>("rect")->h);
	return true;
}

player_detect_input::player_detect_input(shared_ptr<Context> context) : BTNode(context){

}

bool player_detect_input::execute() {
	if (!getter()->getData<SpritePlayer>("spritePlayer")->isAnimationFinished()) {
		return false;
	}
	PlayerState* ps = getter()->getData<PlayerState>("playerState").get();
	auto& input = InputManager::getInstance();
	if (input.isKeyPressed(SDL_SCANCODE_LEFT)) {
		*ps &= ~PlayerState::Right;
		*ps |= PlayerState::Left;
	}
	if (input.isKeyPressed(SDL_SCANCODE_RIGHT)) {
		*ps &= ~PlayerState::Left;
		*ps |= PlayerState::Right;
	}
	if (input.isKeyPressed(SDL_SCANCODE_UP)) {
		if ((bool)(*ps & PlayerState::Down)) {//如果在跳跃则不能下蹲
			*ps |= PlayerState::Jump;
		}
	}
	if (input.isKeyPressed(SDL_SCANCODE_DOWN)) {
		if ((bool)(*ps & PlayerState::Jump)) {//如果在跳跃则不能下蹲
			*ps |= PlayerState::Down;
		}
	}
	if (input.isKeyPressed(SDL_SCANCODE_J)) {
		*ps |= PlayerState::Attack;
	}
	else if (input.isKeyPressed(SDL_SCANCODE_K)) {
		*ps |= PlayerState::Roll;
	}
	return true;
}
//跳跃
player_move_jump::player_move_jump(shared_ptr<Context> context) : BTNode(context) {}

bool player_move_jump::execute() {
	PlayerState* state = getter()->getData<PlayerState>("playerState").get();
	PlayerAttrs* attrs = getter()->getData<PlayerAttrs>("playerAttrs").get();
	//if (!(bool)(*state & PlayerState::Interruptible_mask)) {//如果当前状态除了移动还有别的动作，无法被打断
	//	return false;
	//}
	
	if ((bool)(*state & PlayerState::Jump)) {
		attrs->playerY -= attrs->player_move_speed;
		attrs->playerY = max(attrs->playerY, 0);
		return true;
	}
	return false;
}


//下蹲



player_move_down::player_move_down(shared_ptr<Context> context) : BTNode(context) {}

bool player_move_down::execute() {
	PlayerState* state = getter()->getData<PlayerState>("playerState").get();
	if (!(bool)(*state & PlayerState::Interruptible_mask)) {//如果当前状态除了移动还有别的动作，无法被打断
		return false;
	}
	PlayerAttrs* attrs = getter()->getData<PlayerAttrs>("playerAttrs").get();
	if ((bool)(*state & PlayerState::Down)) {
		//待补充：下蹲矩形缩小
			
		return true;
	}
}


//左移
player_move_left::player_move_left(shared_ptr<Context> context) : BTNode(context) {}

bool player_move_left::execute() {

	PlayerState* state = getter()->getData<PlayerState>("playerState").get();
	if (!(bool)(*state & PlayerState::Interruptible_mask)) {//如果当前状态除了移动还有别的动作，无法被打断
		return false;
	}
	PlayerAttrs* attrs = getter()->getData<PlayerAttrs>("playerAttrs").get();
	if ((bool)(*state & PlayerState::Left)) {
		attrs->player_orientation = false;
		attrs->playerX -= attrs->player_move_speed;
		attrs->playerX = clamp(attrs->playerX, 0.0f, Camera::getInstance().getCameraRange().w - attrs->player_render_width);
		return true;
	}
}

//右移
player_move_right::player_move_right(shared_ptr<Context> context) : BTNode(context) {}

bool player_move_right::execute() {

	PlayerState* state = getter()->getData<PlayerState>("playerState").get();
	if (!(bool)(*state & PlayerState::Interruptible_mask)) {//如果当前状态除了移动还有别的动作，无法被打断
		return false;
	}
	PlayerAttrs* attrs = getter()->getData<PlayerAttrs>("playerAttrs").get();
	if ((bool)(*state & PlayerState::Right)) {
		attrs->player_orientation = true;
		attrs->playerX += attrs->player_move_speed;
		attrs->playerX = clamp(attrs->playerX,0.0f,Camera::getInstance().getCameraRange().w - attrs->player_render_width);
		return true;
	}
}

refreshRect::refreshRect(shared_ptr<Context> context) : BTNode(context) {}

bool refreshRect::execute() {
	PlayerAttrs* attrs = getter()->getData<PlayerAttrs>("playerAttrs").get();
	getter()->getData<SDL_FRect>("rect")->x = attrs->playerX;
	getter()->getData<SDL_FRect>("rect")->y = attrs->playerY;
	return true;
}


//bool player_move_sprite::execute() {
//	float dx = 0, dy = 0;
//	PlayerAttrs* attrs = getter()->getData<PlayerAttrs>("playerAttrs").get();
//
//
//	auto move_speed = player.getAttrs()[player_move_speed];
//	auto [limit_w, limit_h] = Camera::getInstance().getCameraRange();
//	attrs[player_x] += move_speed * dx;
//	attrs[player_y] += move_speed * dy;
//	attrs[player_x] = clamp(attrs[player_x], 0.0f, limit_w - player.getRect().w);
//	attrs[player_y] = clamp(attrs[player_y], 0.0f, limit_h - player.getRect().h);
//	player.setMove(attrs[player_x], attrs[player_y]);
//	return true;
//}


bool CheckComboNode::execute()
{
	bool result = inputBuffer.checkCombo(combo);
	cout << "CheckCombo result: " << (result ? "true" : "false") << endl;
	return result;
}
