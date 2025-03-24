#pragma once
#include "pch.h"
#include <unordered_map>

enum KeyState {
	IDLE,HELD,PRESSED,RELEASED,JUST_RELEASED
};

struct KeyInfo {
	KeyState state = IDLE;
	Uint64 pressTime = 0;
	Uint64 releaseTime = 0;
};

struct MouseInfo {
	int x, y;
	unordered_map<Uint8, KeyInfo> button;
	int wheelY;
};

class InputManager {  
public:
	static InputManager& Instance();

	bool update(const SDL_Event& e);
	void postUpdate();


	//МќХЬ
	bool isKeyIdle(SDL_Scancode key);
	bool isKeyPressed(SDL_Scancode key);
	bool isKeyPressedOnce(SDL_Scancode key);
	bool isKeyHeld(SDL_Scancode key);
	bool isKeyReleased(SDL_Scancode key);
	
	
	
	//ЪѓБъ
	bool isMouseButtonIdle(Uint8 buttonId);
	bool isMouseButtonPressed(Uint8 buttonId);
	bool isMouseButtonHeld(Uint8 buttonId);
	bool isMouseButtonReleased(Uint8 buttonId);

	void getMousexy(int& x, int& y);
	bool isPointInRect(SDL_FRect& rect);
	bool isCursorHovering(SDL_FRect* rect);

	void isSpacePressed();

	void checkAllKeyEvents();

	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

private:
	InputManager();
	~InputManager();
	void handleMouseButtonDown(Uint8 buttonId, MouseInfo& mouse, Uint64 now);
	void handleMouseButtonUp(Uint8 buttonId, MouseInfo& mouse, Uint64 now);

	vector<bool> keyState;
	unordered_map<SDL_Scancode, KeyInfo> keys;
	MouseInfo mouse;

	const Uint64 LONG_PRESS_THRESHOLD = 500;
	Uint64 last_frame_select_time;
	const Uint64 FRAME_SELECTED_THRESHOLD = 1;
};