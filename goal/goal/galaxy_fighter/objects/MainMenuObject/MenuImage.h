#pragma once
#include "pch.h"
#include "../../BehaviorTree/Composite/Selector.h"
#include "../../BehaviorTree/paralle/ParalleNode.h"

class MenuButton
{
public:
	MenuButton(SDL_Texture* texture, float scale, float x, float y);
			  //贴图                 缩放因子      x坐标     y坐标
	SDL_FRect& getRect();
	void update();
private:
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	vector<float> attrs;
	SDL_FRect rect;

	bool isSelecting;
	unique_ptr<ParalleNode> root;
};

class MenuBackground
{
public:
	MenuBackground(SDL_Texture* texture);
	void update();
private:
	SDL_Texture* texture;
	unique_ptr<ParalleNode> root;
};
