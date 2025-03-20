#include "pch.h"
#include "BTAction_player.h"
//
//using namespace BTAction_player;
//
////display_at_position::display_at_position(SDL_Texture* texture, SDL_FRect* rect, double angle) {
////	this->texture = texture;
////	this->rect = rect;
////	this->angle = angle;
////}
//
////bool display_at_position::execute() {
////	
	//SDL_RenderTextureRotated(RendererManager::Instance().getRenderer(), texture, nullptr, rect, angle, nullptr, SDL_FLIP_NONE)) {
////		return true;
////	}
////	else {
////		SDL_Log("��Ⱦ����ʧ��");
////		return false;
////	}
////}
//
//
//display_at_center::display_at_center(SDL_Texture* texture,SDL_FRect* parentRect,double angle)
//{
//	Camera& camera = Camera::Instance();
//	windowRect = &Resolution::Instance().getWindowRect();
//	rect_show = {0,0,parentRect->w,parentRect->h};
//	this->parentRect = parentRect;
//	this->texture = texture;
//	this->angle = angle;
//}
//
//bool display_at_center::execute()
//{
//	auto isCrashed = Camera::Instance().ownerxyCrashedState();
//	if (isCrashed.first) {
//		rect_show.x = parentRect->x - Camera::Instance().getViewport()->x;
//	}
//	else rect_show.x = windowRect->w / 2 - parentRect->w / 2;
//	if(isCrashed.second){
//		rect_show.y = parentRect->y - Camera::Instance().getViewport()->y;
//	}
//	else rect_show.y = windowRect->h / 2 - parentRect->h / 2;
//	if (SDL_RenderTextureRotated(RendererManager::Instance().getRenderer(), texture, nullptr, &rect_show, angle, nullptr, SDL_FLIP_NONE)) {
//		return true;
//	}
//	else {
//		SDL_Log("��Ⱦ����ʧ��");
//		return false;
//	}
//}
//
//
//display_anime_at_center::display_anime_at_center(SDL_Texture* texture, SDL_FRect& spriteFrameRect,SDL_FRect* parentRect, double angle,bool* isTowardRight) : spriteFrameRect(spriteFrameRect)
//{
//	Camera& camera = Camera::Instance();	
//	windowRect = &Resolution::Instance().getWindowRect();
//	rect_show = { 0,0,parentRect->w,parentRect->h };
//	this->parentRect = parentRect;
//	this->texture = texture;
//	this->angle = angle;
//	this->spriteFrameRect = spriteFrameRect;
//	this->isTowardRight = isTowardRight;
//}
//
//bool display_anime_at_center::execute() {
//	auto isCrashed = Camera::Instance().ownerxyCrashedState();
//	if (isCrashed.first) {
//		rect_show.x = parentRect->x - Camera::Instance().getViewport()->x;
//	} else {
//		rect_show.x = windowRect->w / 2 - parentRect->w / 2;
//	} 
//	if (isCrashed.second) {
//		rect_show.y = parentRect->y - Camera::Instance().getViewport()->y;
//	} else {
//		rect_show.y = windowRect->h / 2 - parentRect->h / 2;
//	}
//	if (SDL_RenderTextureRotated(RendererManager::Instance().getRenderer(), texture, &spriteFrameRect, &rect_show, angle, nullptr, (*isTowardRight) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL)) {
//		return true;
//	} else {
//		SDL_Log("��Ⱦ����ʧ��");
//		return false;
//	}
//}
//
//
//
//
//player_move_image::player_move_image(shared_ptr<Context> context) : BTNode(context){
//
//}
//
//bool player_move_image::execute() {
//	float dx = 0, dy = 0;
//	PlayerAttrs* attrs = getter()->getData<PlayerAttrs>("playerAttrs").get();
//	
//	const bool* keystate = SDL_GetKeyboardState(nullptr);
//	if (keystate[SDL_SCANCODE_UP]) dy -= 1;
//	if (keystate[SDL_SCANCODE_LEFT]) dx -= 1;
//	if (keystate[SDL_SCANCODE_DOWN]) dy += 1;
//	if (keystate[SDL_SCANCODE_RIGHT]) dx += 1;
//	
//	float length = std::sqrt(dy*dy + dx*dx);
//
//	if (length > 0) {
//		dx /= length;
//		dy /= length;
//		//getter()->getData<PlayerObject>("this")->removePlayerState(PlayerState::Idle);
//	}
//	else {
//		//getter()->getData<PlayerObject>("this")->setPlayerState(PlayerState::Idle);
//		return false;
//	}
//	//auto move_speed = attrs->player_move_speed;
//	//auto [limit_w, limit_h] = Camera::Instance().getCameraRange();
//	//attrs->playerX += move_speed * dx;
//	//attrs->playerY += move_speed * dy;
//	//attrs->playerX = clamp(attrs->playerX, 0.0f, limit_w - getter()->getData<SDL_FRect>("rect")->w);
//	//attrs->playerY = clamp(attrs->playerY, 0.0f, limit_h - getter()->getData<SDL_FRect>("rect")->h);
//	return true;
//}
//
//player_detect_input::player_detect_input(shared_ptr<Context> context) : BTNode(context){
//
//}
//
//bool player_detect_input::execute() {
//
//	return true;
//}
//
//static std::queue<PlayerState> action;
//
////��Ծ
//player_move_jump::player_move_jump(shared_ptr<Context> context) : BTNode(context) {}
//
//bool player_move_jump::execute() {
//	InputManager& input = InputManager::Instance();
//	PlayerState* state = getter()->getData<PlayerState>("playerState").get();
//	PlayerAttrs* attrs = getter()->getData<PlayerAttrs>("playerAttrs").get();
//	auto is_on_ground = getter()->getData<bool>("isOnGround").get();
//
//	static const float jumpStrength = 8.0f; // ��Ծ���ٶ�
//
//	if ((bool)(*state & PlayerState::Idle_to_Jump)) {
//		*state &= ~PlayerState::Idle_to_Jump;
//	}
//	if (input.isKeyPressed(SDL_SCANCODE_UP) && *is_on_ground) {
//		attrs->velocityY = -jumpStrength;
//		*state |= PlayerState::Jump;
//		*state |= PlayerState::Idle_to_Jump;
//		
//	}
//	if (input.isKeyReleased(SDL_SCANCODE_UP) || attrs->velocityY >= 0) {
//		*state &= ~PlayerState::Jump;
//	}
//	if ((bool)(*state & PlayerState::Jump)) {//����Ծ�����Ӹ߶Ⱥͽ�����Ծ�ٶ�
//		attrs->playerY -= attrs->velocityY;
//		attrs->velocityY += attrs->gravity;
//	}
//	return true;
//}
//
//
////��׹
//player_move_fall::player_move_fall(shared_ptr<Context> context) : BTNode(context) {}
//bool player_move_fall::execute()
//{	
//
//	PlayerState* state = getter()->getData<PlayerState>("playerState").get();
//	PlayerAttrs* attrs = getter()->getData<PlayerAttrs>("playerAttrs").get();
//	auto is_on_ground = getter()->getData<bool>("isOnGround").get();
//
//	static const float MaxFallStrength = 8.0f; // ��������ٶ�
//
//	if (!(bool)(*state & PlayerState::Jump)) 
//	{
//		//������Ծ
//		if (!(bool)(*state & PlayerState::Fall)) 
//		{
//			//����׹��
//			if (*is_on_ground) {//�ڵ�����
//				*state &= ~PlayerState::Fall;
//			}
//			else {
//				*state |= PlayerState::Fall;
//				attrs->velocityY = 0;
//				//action.push(PlayerState::Fall);
//			}
//		}
//
//	}
//	if ((bool)(*state & PlayerState::Fall)) {//����ڽ���
//		attrs->playerY += attrs->velocityY;//��ҵ���
//		attrs->velocityY = min(MaxFallStrength, attrs->velocityY + attrs->gravity);//����������ٶ�����
//	}
//	return true;
//}
//
//
//player_move_down::player_move_down(shared_ptr<Context> context) : BTNode(context) {}
//bool player_move_down::execute() {
//	PlayerState* state = getter()->getData<PlayerState>("playerState").get();
//	if (!(bool)(*state & PlayerState::Interruptible_mask)) {//�����ǰ״̬�����ƶ����б�Ķ������޷������
//		return false;
//	}
//	PlayerAttrs* attrs = getter()->getData<PlayerAttrs>("playerAttrs").get();
//	if ((bool)(*state & PlayerState::Down)) {
//		//�����䣺�¶׾�����С
//			
//		return true;
//	}
//}
//
//
//
//
////�ܲ�
//player_move_run::player_move_run(shared_ptr<Context> context) : BTNode(context) {}
//bool player_move_run::execute() {
//
//	InputManager& input = InputManager::Instance();
//	PlayerState* state = getter()->getData<PlayerState>("playerState").get();
//	PlayerAttrs* attrs = getter()->getData<PlayerAttrs>("playerAttrs").get();
//
//	bool isRunning = (bool)(*state & PlayerState::Run);
//	bool facingRight = attrs->player_orientation;
//
//	// �ٶ� & �������
//	float& vx = attrs->velocityX;
//	const float ax = 0.4f;      // ���ٶ�
//	const float maxSpeed = 4.0f; // ����ٶ�
//	const float friction = 0.2f; // Ħ����
//
//
//	if (input.isKeyPressed(SDL_SCANCODE_LEFT)) {
//		attrs->player_orientation = false;
//		vx -= ax;
//	}
//	else if (input.isKeyPressed(SDL_SCANCODE_RIGHT)) {
//		attrs->player_orientation = true;
//		vx += ax;
//	}
//	else {
//		*state &= ~PlayerState::Run;
//		// ʩ��Ħ����
//		if (vx > 0) {
//			vx -= friction;
//			if (vx < 0) vx = 0;
//		}
//		else if (vx < 0) {
//			vx += friction;
//			if (vx > 0) vx = 0;
//		}
//	}
//
//	// ��������ٶ�
//	vx = std::clamp(vx, -maxSpeed, maxSpeed);
//
//	// ����λ��
//	attrs->playerX += vx;
//	return true;
//}
//
//refreshRect::refreshRect(shared_ptr<Context> context) : BTNode(context) {}
//
//bool refreshRect::execute() {
//	PlayerAttrs* attrs = getter()->getData<PlayerAttrs>("playerAttrs").get();
//	getter()->getData<SDL_FRect>("rect")->x = attrs->playerX;
//	getter()->getData<SDL_FRect>("rect")->y = attrs->playerY;
//	return true;
//}
//
//
//
//
//
//bool CheckComboNode::execute()
//{
//	bool result = inputBuffer.checkCombo(combo);
//	cout << "CheckCombo result: " << (result ? "true" : "false") << endl;
//	return result;
//}
//
//
//
//
//
////�Ƿ��ڵ���
//is_on_ground::is_on_ground(shared_ptr<Context> context) : BTNode(context){}
//
//bool is_on_ground::execute()
//{
//
//	auto attrs = getter()->getData<PlayerAttrs>("playerAttrs");
//	auto state = getter()->getData<PlayerState>("playerState");
//	auto ground = getter()->getData<bool>("isOnGround");
//	if (attrs->playerY >= 800) {
//
//		*state |= PlayerState::On_ground;
//		*state &= ~PlayerState::Jump;
//		*state &= ~PlayerState::Fall;
//		attrs->playerY = 800;
//		*ground = true;
//		return true;
//	}
//	else {
//		*getter()->getData<PlayerState>("playerState") &= ~PlayerState::On_ground;
//		*ground = false;
//	}
//	return false;
//}
