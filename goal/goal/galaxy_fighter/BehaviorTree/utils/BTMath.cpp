#include "pch.h"
#include "BTMath.h"

float BTMath::Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

float BTMath::SmoothStep(float t) {
	return t * t * t * (t * (t * 6 - 15) + 10);
}

float BTMath::SmoothAcceleration()
{
	return 0.0f;
}

