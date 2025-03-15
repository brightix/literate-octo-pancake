#pragma once
#include "../objects/playerObject/PlayerState.h"

class TransformUtils
{
	
public:
	std::unordered_map<std::string, PlayerState> string2playerState;
	TransformUtils();
};

