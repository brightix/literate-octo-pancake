#pragma once
#include <vector>
#include <utility>

class Resolution
{
public:
	static Resolution& getInstance();

	void setResolution(short level);
	void setLandScape(bool b);
	SDL_FRect& getWindowRect();
	bool getIsLandScape();

	float getScaleFactor();

	Resolution(const Resolution&) = delete;
	Resolution& operator=(const Resolution&) = delete;
private:
	Resolution();
	~Resolution();
	//·Ö±æÂÊ
	short curRes;
	bool isLandScape;
	SDL_FRect windowRect;
	std::vector<std::pair<float, float>> resolution;
};

