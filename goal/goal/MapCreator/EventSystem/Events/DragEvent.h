#pragma once
#include "pch.h"
#include "Event.h"
class DragToOtherEvent 
	: public Event 
{
public:
	std::string CurWindow;
	SDL_FRect otherWindow;
	float scale;
	DragToOtherEvent(std::string& name, SDL_FRect otherWindow,float scale) : CurWindow(name),otherWindow(otherWindow),scale(scale) {}
};