#include "pch.h"
#include "../Event.h"

class SwitchHoveringWindow 
	:public Event
{
public:
	std::string WindowName;
	SwitchHoveringWindow(std::string WindowName) : WindowName(WindowName) {}
};