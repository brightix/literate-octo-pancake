#pragma once
#include "pch.h"
class InputBuffer
{
	std::queue<std::pair<std::string, Uint64>> buffer;
	int maxBufferSize = 5;
	int maxTimeGap = 500;
public:
	void registerInput(const std::string& key);
	bool checkCombo(const vector<string>& combo);
};

