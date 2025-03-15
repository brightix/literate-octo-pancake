#pragma once
#include "pch.h"
#include "../../objects/baseObject.h"

constexpr int MAX_OBJECTS = 4;
constexpr int MAX_DEPTH = 4;

class QuadTreeNode
{
	SDL_FRect boundary;
	int capacity;
	std::vector<BaseObject> objects;
	QuadTreeNode* children[4];
public:
	QuadTreeNode(SDL_FRect boundary);

	void inset(BaseObject& obj);

	bool isWithinBoundary(BaseObject& obj);

	void subdivide();

};



