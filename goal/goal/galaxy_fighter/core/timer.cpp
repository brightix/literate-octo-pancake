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
	deltaTime = (float)(currentTime.QuadPart - lastTime.QuadPart) / frequency.QuadPart;

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
	return (deltaTime / BASE_FRAME_TIME)*globalSpeed;
}

const void Timer::sleep(double duration) {
	LARGE_INTEGER preTime,curTime;
	QueryPerformanceCounter(&preTime);

	double delta = 0;
	while (duration - delta > 0.003) {
		Sleep(1);
		QueryPerformanceCounter(&curTime);
		delta = (float)(curTime.QuadPart - preTime.QuadPart) / frequency.QuadPart;
	}
	while (delta < duration) {
		QueryPerformanceCounter(&curTime);
		delta = (float)(curTime.QuadPart - preTime.QuadPart) / frequency.QuadPart;
	}
}



double Timer::getRefreshTime() {
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	double adjustedSleepTime = refreshTime - (float)(t.QuadPart - currentTime.QuadPart) / frequency.QuadPart;
	return adjustedSleepTime > 0.0 ? adjustedSleepTime : 0.0;

}

void Timer::selectFrame(int level) {
	curFrameLevel = level;
	if(0 <= level && level < frameTable.size())
		refreshTime = 1/frameTable[curFrameLevel];
	else {
		GameWorld::Instance().addError("设置帧率越界");
	}
}

void Timer::reset() {
	QueryPerformanceFrequency(&frequency);
	ticks = 0;
}

void Timer::myPrint(string str, double val) {
	cout << str << val << endl;
}

void Timer::startCountTimer(string task) {
	if (countTimer.find(task) == countTimer.end()) {
		LARGE_INTEGER startTime;
		QueryPerformanceCounter(&startTime);
		cout << "创建了 " << task << " 的计时任务" << endl;
		countTimer[task] = startTime;
	}
	QueryPerformanceCounter(&countTimer[task]);
}

void Timer::returnCountTimer(string task) {
	if (countTimer.find(task) == countTimer.end()) {
		cout << "没有名为 " << task << " 的任务" << endl;
		return;
	}

	LARGE_INTEGER endTimer;
	QueryPerformanceCounter(&endTimer);
	float time = (endTimer.QuadPart - countTimer[task].QuadPart) * 1000.0 / frequency.QuadPart;
	cout << task << " 的计时结果为" << time << endl;
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

//int Timer::getFrame() {
//	return 1000 / refreshTime;
//}

int Timer::getCurFrame() {
	return frameTable[curFrameLevel];
}

Timer::Timer() {
	init();
}

Timer::~Timer() {
}

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


