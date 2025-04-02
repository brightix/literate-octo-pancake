#pragma once
#include "pch.h"
#include "../utils/CircularQueue.h"

typedef struct KeyBuffer {
	SDL_Scancode KeyId;
	double KeyPressTime;
}KeyBuffer;

class InputBuffer {
	CircularQueue<KeyBuffer> buffer;
	double bufferDelay = 0.5;
public:
	InputBuffer() {

	}
	void addInput(SDL_Scancode code) {
		double now = Timer::Instance().getTicks();
		buffer.push({code,now});
	}
	void update() {
		double now = Timer::Instance().getTicks();
		while (buffer.size() > 0 && now - buffer.back().KeyPressTime > bufferDelay) {
			buffer.pop();
		}
	}
	bool isBuffered(SDL_Scancode code) {
		int i = buffer.getHead();
		int m = buffer.size();
		int n = i + m;

		for (int i = buffer.getHead();i < n;i++) {
			if (buffer[i%m].KeyId == code) {
				buffer.clear();
				return true;
			}
		}
		return false;
	}
	bool isBuffered(std::vector<SDL_Scancode> combo) {
		int m = buffer.size();
		std::vector<int> next(m, 0);
		int i = 0;
		for (int j = 1;j < m;j++) {
			while (i != 0 && buffer[j].KeyId != buffer[i].KeyId) {
				i = next[i - 1];
			}
			if (buffer[i].KeyId == buffer[j].KeyId) {
				i++;
			}
			next[j] = i;
		}
		int n = combo.size();
		i = 0;
		for (int j = 0;j < n;j++) {
			while (combo[j] != buffer[i].KeyId && i != 0) {
				i = next[i - 1];
			}
			if (combo[j] == buffer[i].KeyId) {
				i++;
			}
			if (i == m) {
				buffer.clear();
				return true;
			}
		}
		return false;
	}
};

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
	bool isKeyPressedBuffered(SDL_Scancode key);
	bool isKeyReleased(SDL_Scancode key);

	Uint64 getLastPressdTime(SDL_Scancode key);
	
	
	
	//ЪѓБъ
	bool isMouseButtonIdle(Uint8 buttonId);
	bool isMouseButtonPressed(Uint8 buttonId);
	bool isMouseButtonHeld(Uint8 buttonId);
	bool isMouseButtonReleased(Uint8 buttonId);

	bool isMouseWheelYScrollUp();

	bool isMouseWheelYScrollDown();

	int isMouseWheelYScrolled();
	pair<float, float> getMousexy();
	pair<float,float> getRelativeMousexy();
	void setRelativeMouseMode(bool b);
	bool isPointInRect(SDL_FRect& rect);
	bool isCursorHovering(SDL_FRect* rect);

	void isSpacePressed();

	void checkAllKeyEvents();

	void switchToEnglishInput();

	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

private:
	InputManager();
	~InputManager();
	InputBuffer inputBuffer;
	void handleMouseButtonDown(Uint8 buttonId, MouseInfo& mouse, Uint64 now);
	void handleMouseButtonUp(Uint8 buttonId, MouseInfo& mouse, Uint64 now);

	vector<bool> keyState;
	unordered_map<SDL_Scancode, KeyInfo> keys;
	MouseInfo mouse;


	const Uint64 LONG_PRESS_THRESHOLD = 500;
	Uint64 last_frame_select_time;
	const Uint64 FRAME_SELECTED_THRESHOLD = 1;
};


