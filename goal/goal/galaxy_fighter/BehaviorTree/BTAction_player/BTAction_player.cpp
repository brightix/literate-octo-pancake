#include "pch.h"
#include "BTAction_player.h"

using namespace BTAction_player;

display_at_position::display_at_position(SDL_Texture* texture, SDL_FRect* rect, double angle) {
	this->texture = texture;
	this->rect = rect;
	this->angle = angle;
}

bool display_at_position::execute() {
	
	if (SDL_RenderTextureRotated(RendererManager::getInstance().getRenderer(), texture, nullptr, rect, angle, nullptr, SDL_FLIP_NONE)) {
		return true;
	}
	else {
		SDL_Log("äÖÈ¾ÎÆÀíÊ§°Ü");
		return false;
	}
}


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
		SDL_Log("äÖÈ¾ÎÆÀíÊ§°Ü");
		return false;
	}
}


display_anime_at_center::display_anime_at_center(SDL_Texture* texture, SDL_FRect* srcRect,SDL_FRect* parentRect, double angle)
{
	Camera& camera = Camera::getInstance();
	windowRect = &Resolution::getInstance().getWindowRect();
	rect_show = { 0,0,parentRect->w,parentRect->h };
	this->spriteFrameRect = srcRect;
	this->parentRect = parentRect;
	this->texture = texture;
	this->angle = angle;
	this->anime_play_time = 0.0;
}

bool display_anime_at_center::execute() {
	auto isCrashed = Camera::getInstance().ownerxyCrashedState();
	if (isCrashed.first) {
		rect_show.x = parentRect->x - Camera::getInstance().getViewport()->x;
	}
	else rect_show.x = windowRect->w / 2 - parentRect->w / 2;
	if (isCrashed.second) {
		rect_show.y = parentRect->y - Camera::getInstance().getViewport()->y;
	}
	else rect_show.y = windowRect->h / 2 - parentRect->h / 2;
	if (SDL_RenderTextureRotated(RendererManager::getInstance().getRenderer(), texture, spriteFrameRect, &rect_show, angle, nullptr, SDL_FLIP_NONE)) {
		return true;
	}
	else {
		SDL_Log("äÖÈ¾ÎÆÀíÊ§°Ü");
		return false;
	}
}




player_move_image::player_move_image(PlayerObject& player) : player(player){

}

bool player_move_image::execute() {
	float dx = 0, dy = 0;
	auto& attrs = player.getAttrs();
	
	const bool* keystate = SDL_GetKeyboardState(nullptr);
	if (keystate[SDL_SCANCODE_UP]) dy -= 1;
	if (keystate[SDL_SCANCODE_LEFT]) dx -= 1;
	if (keystate[SDL_SCANCODE_DOWN]) dy += 1;
	if (keystate[SDL_SCANCODE_RIGHT]) dx += 1;
	
	float length = std::sqrt(dy*dy + dx*dx);

	if (length > 0) {
		dx /= length;
		dy /= length;
		player.removePlayerState(PlayerState::Idle);
	}
	else {
		player.setPlayerState(PlayerState::Idle);
		return false;
	}
	auto move_speed = player.getAttrs()[player_move_speed];
	auto [limit_w, limit_h] = Camera::getInstance().getCameraRange();
	attrs[player_x] += move_speed * dx;
	attrs[player_y] += move_speed * dy;
	attrs[player_x] = clamp(attrs[player_x],0.0f,limit_w - player.getRect().w);
	attrs[player_y] = clamp(attrs[player_y], 0.0f, limit_h - player.getRect().h);
	player.setMove(attrs[player_x], attrs[player_y]);
	return true;
}



player_move_sprite::player_move_sprite(PlayerObject& player) : player(player) {

}

bool player_move_sprite::execute() {
	float dx = 0, dy = 0;
	auto& attrs = player.getAttrs();

	const bool* keystate = SDL_GetKeyboardState(nullptr);
	if (keystate[SDL_SCANCODE_UP]) dy -= 1;
	if (keystate[SDL_SCANCODE_LEFT]) dx -= 1;
	if (keystate[SDL_SCANCODE_DOWN]) dy += 1;
	if (keystate[SDL_SCANCODE_RIGHT]) dx += 1;

	float length = std::sqrt(dy * dy + dx * dx);

	if (length > 0) {
		dx /= length;
		if (dx < 0) {
			player.setPlayerState(PlayerState::Left);
		}
		else if (dx > 0) {
			player.setPlayerState(PlayerState::Right);
		}
		if (dy < 0) {
			player.setPlayerState(PlayerState::Down);
		}
		else if (dy > 0) {
			player.setPlayerState(PlayerState::Jump);
		}
	}
	else {
		player.setPlayerState(PlayerState::Idle);
		return false;
	}
	player.refreshAnimationTime();

	auto move_speed = player.getAttrs()[player_move_speed];
	auto [limit_w, limit_h] = Camera::getInstance().getCameraRange();
	attrs[player_x] += move_speed * dx;
	attrs[player_y] += move_speed * dy;
	attrs[player_x] = clamp(attrs[player_x], 0.0f, limit_w - player.getRect().w);
	attrs[player_y] = clamp(attrs[player_y], 0.0f, limit_h - player.getRect().h);
	player.setMove(attrs[player_x], attrs[player_y]);
	return true;
}

cal_sprite_rect::cal_sprite_rect(){
	
}

bool cal_sprite_rect::execute()
{

	return true;
}
