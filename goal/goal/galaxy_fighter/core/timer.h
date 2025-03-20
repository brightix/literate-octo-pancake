#pragma once
#include "pch.h"

using namespace std;

typedef struct s s;
//��ʱ��
class Timer {
public:
	static Timer& Instance();

	void update();
	Uint64 getTicks() const;
	double getDeltaTime() const;//��ȡʱ����

	double getDeltaAdjustTime() const ;
	double getVelocityFactor();
	const void sleep(double duration);
	double getRefreshTime();
	void selectFrame(int level);
	void reset();
	void myPrint(string str, double val);
	double calDeltaOnce();//��������,ÿ��ֻ��ʹ��һ�Σ�������ʵ�������
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

	LARGE_INTEGER frequency;//��ʱ��Ƶ��
	LARGE_INTEGER lastTime;
	LARGE_INTEGER currentTime;
	LARGE_INTEGER pauseTime;


	Uint64 ticks;//ʱ����
	double deltaTime;//ˢ��һ֡����Ҫ��ʱ��
	bool isPause = false;

	LARGE_INTEGER testDeltaBegin;
	LARGE_INTEGER testDeltaEnd;

	double velocityFactor;//�ٶ�����
	double refreshTime;

	vector<double> frameTable;
	void init();
};



//������
typedef struct Buffer {
	Buffer();
	//~Buffer();
	TCHAR heroBloodText[20];
	TCHAR fpsText[20];//fps��������
	TCHAR scoreText[20];//�÷��ı���������
private:
	void init();
}Buffer;
