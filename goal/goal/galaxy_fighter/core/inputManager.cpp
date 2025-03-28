#include "pch.h"
#include "InputManager.h"


InputManager& InputManager::Instance() {
	static InputManager instance;
	return instance;
}

bool InputManager::update(const SDL_Event& e) {
	Uint64 now = Timer::Instance().getTicks();
	SDL_Scancode KeyId = e.key.scancode;
	KeyInfo& curKey = keys[KeyId];
	switch (e.type) {
	case SDL_EVENT_QUIT:
		return false;
	case SDL_EVENT_KEY_DOWN:
		if (curKey.state == IDLE) {
			inputBuffer.addInput(KeyId);
			curKey.state = PRESSED;
			curKey.pressTime = now;
		}
		break;
	case SDL_EVENT_KEY_UP:
		curKey.state = RELEASED;
		curKey.releaseTime = now;
		break;
	case SDL_EVENT_MOUSE_MOTION:
		mouse.x = e.motion.x;
		mouse.y = e.motion.y;
		break;
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
		handleMouseButtonDown(e.button.button, mouse, now);
		break;
	case SDL_EVENT_MOUSE_BUTTON_UP:
		handleMouseButtonUp(e.button.button,mouse,now);
		break;
	case SDL_EVENT_MOUSE_WHEEL:
		mouse.wheelY = e.wheel.y;
		break;
	default:
		break;
	}
	return true;
}



//bool InputManager::update(const SDL_Event& e) {
//	Uint64 now = Timer::Instance().getTicks();
//	KeyInfo& curKey = keys[e.key.scancode];
//	switch (e.type) {
//	case SDL_EVENT_QUIT:
//		return false;
//	case SDL_EVENT_KEY_DOWN:
//		if (curKey.state == IDLE || curKey.state == RELEASED) {
//			curKey.state = PRESSED;
//			curKey.pressTime = now;
//		}
//		break;
//	case SDL_EVENT_KEY_UP:
//		curKey.state = JUST_RELEASED;
//		curKey.releaseTime = now;
//		break;
//	case SDL_EVENT_MOUSE_MOTION:
//		mouse.x = e.motion.x;
//		mouse.y = e.motion.y;
//		break;
//	case SDL_EVENT_MOUSE_BUTTON_DOWN:
//		handleMouseButtonDown(e.button.button, mouse, now);
//		break;
//	case SDL_EVENT_MOUSE_BUTTON_UP:
//		handleMouseButtonUp(e.button.button,mouse,now);
//		break;
//		//case SDL_EVENT_WINDOW_FOCUS_GAINED
//	default:
//		SDL_Log("input erro %d",e.type);
//	}
//	return true;
//}

void InputManager::handleMouseButtonDown(Uint8 buttonId,MouseInfo& mouse, Uint64 now) {
	auto& btn = mouse.button.at(buttonId);
	if (btn.state == IDLE || btn.state == RELEASED) {
		btn.state = PRESSED;
		btn.pressTime = now;
	}
}

void InputManager::handleMouseButtonUp(Uint8 buttonId, MouseInfo& mouse, Uint64 now) {
	auto& btn = mouse.button.at(buttonId);
	btn.state = RELEASED;
	btn.releaseTime = now;
}

void InputManager::postUpdate() {
	Uint64 now = Timer::Instance().getTicks();
	for (auto& [key, info] : keys) {
		if (info.state == PRESSED) {
			info.state = HELD;
		}
		//else if (info.state == JUST_RELEASED) {
		//	info.state = RELEASED;
		//}
		else if (info.state == RELEASED) {
			info.state = IDLE;
		}

	}
	mouse.wheelY = 0;
}


bool InputManager::isKeyIdle(SDL_Scancode key) { return keys[key].state == IDLE; }
bool InputManager::isKeyPressed(SDL_Scancode key) { return keys[key].state == PRESSED || keys[key].state == HELD; }
bool InputManager::isKeyPressedOnce(SDL_Scancode key) { return keys[key].state == PRESSED; }
bool InputManager::isKeyHeld(SDL_Scancode key) { return keys[key].state == HELD; }
bool InputManager::isKeyReleased(SDL_Scancode key) { return keys[key].state == RELEASED; }
Uint64 InputManager::getLastPressdTime(SDL_Scancode key) {
	return keys[key].releaseTime;
}

//»º³å¼üÎ»
	//bool InputManager::isKeyIdle(SDL_Scancode key) { return keys[key].state == IDLE; }
	bool InputManager::isKeyPressedBuffered(SDL_Scancode key) { return inputBuffer.isBuffered(key); }
	//bool InputManager::isKeyPressedOnce(SDL_Scancode key) { return keys[key].state == PRESSED; }
	//bool InputManager::isKeyHeld(SDL_Scancode key) { return keys[key].state == HELD; }
	//bool InputManager::isKeyReleased(SDL_Scancode key) { return keys[key].state == RELEASED; }

//* * * Êó±ê * * *

bool InputManager::isMouseButtonIdle(Uint8 buttonId) { return mouse.button.at(buttonId).state == IDLE; }
bool InputManager::isMouseButtonPressed(Uint8 buttonId) { return mouse.button.at(buttonId).state == PRESSED; }
bool InputManager::isMouseButtonHeld(Uint8 buttonId) { return mouse.button.at(buttonId).state == HELD; }
bool InputManager::isMouseButtonReleased(Uint8 buttonId) { return mouse.button.at(buttonId).state == RELEASED; }

bool InputManager::isMouseWheelYScrollUp() { return mouse.wheelY > 0; }
bool InputManager::isMouseWheelYScrollDown() { return mouse.wheelY < 0; }
int InputManager::isMouseWheelYScrolled() { return mouse.wheelY; }

pair<int, int> InputManager::getMousexy() { return { mouse.x, mouse.y }; }
pair<float, float> InputManager::getRelativeMousexy() {
	float x, y;
	SDL_GetRelativeMouseState(&x,&y);
	return { x,y };
}

void InputManager::setRelativeMouseMode(bool b) {
	SDL_SetWindowRelativeMouseMode(RendererManager::Instance().getWindow(),b);
}

bool InputManager::isPointInRect(SDL_FRect& rect) {
	if (isMouseButtonPressed(SDL_BUTTON_LEFT) && rect.x <= mouse.x && mouse.x <= rect.x + rect.w && rect.y <= mouse.y && mouse.y <= rect.y + rect.h) {
		return true;
	}
	return false;
}

bool InputManager::isCursorHovering(SDL_FRect* rect) {
	if (rect->x <= mouse.x && mouse.x <= rect->x + rect->w && rect->y <= mouse.y && mouse.y <= rect->y + rect->h) {
		return true;
	}
	return false;
}



void InputManager::isSpacePressed() {
	if (isKeyReleased(SDL_SCANCODE_SPACE)) {
		Timer& timer = Timer::Instance();
		if (timer.getIsPause()) {
			timer.resume();
		}
		else {
			timer.pause();
		}
	}
}

SDL_Scancode& operator++(SDL_Scancode& lhs) {
	lhs = static_cast<SDL_Scancode>(static_cast<int>(lhs) + 1);
	return lhs;
}

void InputManager::checkAllKeyEvents() {
	Uint64 now = Timer::Instance().getTicks();
	if (now - last_frame_select_time >= FRAME_SELECTED_THRESHOLD) {
		for (SDL_Scancode i = SDL_SCANCODE_1;i <= SDL_SCANCODE_4;++i) {
			if (isKeyPressed(i)) {
				Timer::Instance().selectFrame(i - SDL_SCANCODE_1);
				last_frame_select_time = now;
				break;
			}
		}
		if (isKeyPressed(SDL_SCANCODE_5)) {
			RendererManager::Instance().switchScreenDisplayMove();
			last_frame_select_time = now;
		}
	}
}

void InputManager::switchToEnglishInput() {
	keybd_event(VK_SHIFT,0,0,0);
	keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
}

InputManager::InputManager() {
	keys = { {SDL_SCANCODE_1,KeyInfo()},
			{SDL_SCANCODE_2,KeyInfo()},
			{SDL_SCANCODE_3,KeyInfo()},
			{SDL_SCANCODE_4,KeyInfo()},
			{SDL_SCANCODE_SPACE,KeyInfo()},
	};
	mouse = { 0,0,{
		{SDL_BUTTON_LEFT,KeyInfo()},
		{SDL_BUTTON_RIGHT,KeyInfo()},
		{SDL_BUTTON_MIDDLE,KeyInfo()},
	},0 };
}
InputManager::~InputManager() {}