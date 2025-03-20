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
	bool getRandomBool(double probability);
	double enemy_spawn_clock;
	double secondTimer;
	
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


	Uint64 ticks;//时间线
	double deltaTime;//刷新一帧所需要的时间
	bool isPause = false;

	LARGE_INTEGER testDeltaBegin;
	LARGE_INTEGER testDeltaEnd;

	double velocityFactor;//速度因子
	double refreshTime;

	vector<double> frameTable;
	void init();
};



//缓冲器
typedef struct Buffer {
	Buffer();
	//~Buffer();
	TCHAR heroBloodText[20];
	TCHAR fpsText[20];//fps缓冲数组
	TCHAR scoreText[20];//得分文本缓冲数组
private:
	void init();
}Buffer;
