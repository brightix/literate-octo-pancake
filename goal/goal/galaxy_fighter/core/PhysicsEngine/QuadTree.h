#pragma once
#include "pch.h"
#include "../../objects/baseObject.h"

constexpr int MAX_OBJECTS = 4;
constexpr int MAX_DEPTH = 4;	

class QuadTree
{
	int level;
	Rect boundary;
	std::vector<BaseObject*> objects;
	std::array<std::unique_ptr<QuadTree>,4> children;
public:
	QuadTree(Rect boundary);

	void inset(BaseObject& obj);

	//bool isWithinBoundary(BaseObject& obj);

	void subdivide();

};



