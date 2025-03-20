#include "pch.h"
#include "timer.h"

Timer& Timer::Instance() {
	static Timer instance;
	return instance;
}

void Timer::update() {
	//先更新last
	lastTime = currentTime;

	//再更新cur
	QueryPerformanceCounter(&currentTime);

	//等于两帧之差
	deltaTime = (currentTime.QuadPart - lastTime.QuadPart) * 1000.0 / frequency.QuadPart;
	//myPrint("deltaTime: ", deltaTime);

	ticks += deltaTime;
}

Uint64 Timer::getTicks() const {
	return ticks;
}

double Timer::getDeltaTime() const {
	return deltaTime;
}

double Timer::getDeltaAdjustTime() const {
	return deltaTime*globalSpeed;
}

double Timer::getVelocityFactor() {
	return deltaTime / BASE_FRAME_TIME;
}

const void Timer::sleep(double duration) {
	LARGE_INTEGER preTime,curTime;
	QueryPerformanceCounter(&preTime);

	double delta = 0;
	
	while (duration - delta > 3.0) {
		Sleep(1);
		QueryPerformanceCounter(&curTime);
		delta = (curTime.QuadPart - preTime.QuadPart) * 1000.0 / frequency.QuadPart;
	}
	while (delta < duration) {
		QueryPerformanceCounter(&curTime);
		delta = (curTime.QuadPart - preTime.QuadPart) * 1000.0 / frequency.QuadPart;
	}
}



double Timer::getRefreshTime() {
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	double adjustedSleepTime = refreshTime - (t.QuadPart - currentTime.QuadPart) * 1000.0 / frequency.QuadPart;
	return adjustedSleepTime > 0.0 ? adjustedSleepTime : 0.0;
}

void Timer::selectFrame(int level) {
	refreshTime = 1000/frameTable[level];
}

void Timer::reset() {
	QueryPerformanceFrequency(&frequency);
	ticks = 0;
}

void Timer::myPrint(string str, double val) {
	cout << str << val << endl;
}

double Timer::calDeltaOnce() {
	LARGE_INTEGER once;
	QueryPerformanceCounter(&once);
	return (once.QuadPart - lastTime.QuadPart) * 1000.0 / frequency.QuadPart;
}

void Timer::pause() {
	if (!isPause) {
		isPause = true;
		QueryPerformanceCounter(&pauseTime);
	}
}

void Timer::resume() {
	if (isPause) {
		isPause = false;
		LARGE_INTEGER resumeTime;
		QueryPerformanceCounter(&resumeTime);
		currentTime.QuadPart += resumeTime.QuadPart - pauseTime.QuadPart;
	}
}

bool Timer::getIsPause() { return isPause; }

void Timer::funcDeltaBegin() {
	QueryPerformanceCounter(&testDeltaBegin);
}

void Timer::funcDeltaEnd() {
	QueryPerformanceCounter(&testDeltaEnd);
	myPrint("改程序运行使用了", (testDeltaEnd.QuadPart - testDeltaBegin.QuadPart) * 1000.0 / frequency.QuadPart);
}

int Timer::getFrame() {
	return 1000 / refreshTime;
}

Timer::Timer() {
	init();
}

Timer::~Timer() {}

void Timer::init() {
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&currentTime);
	deltaTime = 0;
	ticks = 0;
	frameTable = { 240,120,60,30 };
				//8, 4, 2 , 1
	selectFrame(1);
	enemy_spawn_clock = 0;
	secondTimer = 1000;
}

Buffer::Buffer() {
	init();
}

void Buffer::init() {

}


