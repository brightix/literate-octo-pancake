#pragma once
#include <random>

static 	std::random_device rd;
static std::mt19937 gen(rd());

bool getRandomBool(double probability);