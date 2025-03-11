#include "pch.h"
#include "random_utils.h"

bool getRandomBool(double probability) {
	std::bernoulli_distribution dist(probability);
	return dist(gen);
}