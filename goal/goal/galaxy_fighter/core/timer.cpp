#include "pch.h"
#include "Timer.h"

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
	deltaTime = (double)(currentTime.QuadPart - lastTime.QuadPart) / frequency.QuadPart;

	ticks += deltaTime;
}

double Timer::getTicks() const {
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

void Timer::sleep(double duration) {
	LARGE_INTEGER preTime,curTime;
	QueryPerformanceCounter(&preTime);

	double delta = 0;
	timeBeginPeriod(1);
	while (duration - delta > 0.002) {
		Sleep(1);
		QueryPerformanceCounter(&curTime);
		delta = (double)(curTime.QuadPart - preTime.QuadPart) / frequency.QuadPart;
	}
	timeEndPeriod(1);
	while (delta < duration) {
		QueryPerformanceCounter(&curTime);
		delta = (double)(curTime.QuadPart - preTime.QuadPart) / frequency.QuadPart;
	}
}



double Timer::getRefreshTime() {
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	double interval = (double)(t.QuadPart - currentTime.QuadPart) / frequency.QuadPart;
	double adjustedSleepTime = refreshTime - interval;

	return adjustedSleepTime > 0.0 ? adjustedSleepTime : 0.0;
}

void Timer::selectFrame(int level) {
	curFrameLevel = level;
	if (0 <= level && level < frameTable.size()) {
		refreshTime = 1.0/frameTable[curFrameLevel];
		cout << refreshTime << endl;
	}
	else {
		GameWorld::Instance().addError("设置帧率越界");
	}
}

void Timer::reset() {
	QueryPerformanceFrequency(&frequency);
	ticks = 0;
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
	double time = (endTimer.QuadPart - countTimer[task].QuadPart) * 1000.0 / frequency.QuadPart;
	cout << task << " 的计时结果为" << time << endl;
}

void Timer::start() {
	QueryPerformanceCounter(&startTimer);
}

double Timer::end() {
	LARGE_INTEGER endTimer;
	QueryPerformanceCounter(&endTimer);
	return (double)(endTimer.QuadPart - startTimer.QuadPart) / frequency.QuadPart;
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


int Timer::getCurFrame() {
	return frameTable[curFrameLevel];
}

double Timer::printDeltaFromBeginToNow() {
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);
	double res = (double)(now.QuadPart - currentTime.QuadPart) / frequency.QuadPart;
	return res;
}

void Timer::IsSomthingWorngHere() {
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);
	double res = (double)(now.QuadPart - currentTime.QuadPart) / frequency.QuadPart;
	if (res > refreshTime) {
		cout << "here is the point" << endl;
	}
}

void Timer::showFps() {
	TextRenderer& TRenderer = TextRenderer::Instance();
	TRenderer.renderText(0, 0, TRenderer.getTextTexture(to_string((int)(1 / getDeltaAdjustTime())), "pingfang", 20).get());
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