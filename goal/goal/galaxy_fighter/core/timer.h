#pragma once
#include "pch.h"

using namespace std;

typedef struct s s;
//计时器
class Timer {
public:
	static Timer& Instance();

	void update();
	Uint64 getTicks() const;
	double getDeltaTime() const;//获取时间间隔

	double getDeltaAdjustTime() const ;
	double getVelocityFactor();
	const void sleep(double duration);
	double getRefreshTime();
	void selectFrame(int level);
	void reset();
	void myPrint(string str, double val);
	double calDeltaOnce();//开发函数,每次只能使用一次，不用于实际软件内
	void pause();
	void resume();
	bool getIsPause();

	void funcDeltaBegin();
	void funcDeltaEnd();

	int getFrame();
	int getCurFrame();
	bool getRandomBool(double probability);
	double enemy_spawn_clock;
	double secondTimer;
	
	void startCountTimer(std::string task);
	void returnCountTimer(std::string task);

	Timer(const Timer&) = delete;
	Timer& operator=(const Timer&) = delete;
protected:
	

private:
	Timer();
	~Timer();

	LARGE_INTEGER frequency;//计时器频率
	LARGE_INTEGER lastTime;
	LARGE_INTEGER currentTime;
	LARGE_INTEGER pauseTime;


	double ticks;//时间线
	double deltaTime;//刷新一帧所需要的时间
	bool isPause = false;

	LARGE_INTEGER testDeltaBegin;
	LARGE_INTEGER testDeltaEnd;

	double velocityFactor;//速度因子
	double refreshTime;

	vector<double> frameTable;
	int curFrameLevel;
	void init();
	
	//计时器
	std::unordered_map<string, LARGE_INTEGER> countTimer;
};

