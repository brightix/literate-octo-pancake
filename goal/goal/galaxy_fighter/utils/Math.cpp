#include "pch.h"
#include "Math.h"

#define PI 3.14159265358979323846

float Math::Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

float Math::SmoothStep(float t) {
	return t * t * t * (t * (t * 6 - 15) + 10);
}

float Math::SmoothAcceleration()
{
	return 0.0f;
}
	
double Math::SinInterpolation(float a,float b,float t) {
	return a + (b-a) * sin(t * PI/2);
}

double Math::CosInterpolation(float a, float b, float t) {
	return a + (b - a) * (1 - cos(t * PI)) / 2;
}

double Math::ExpInterpolation(float a, float b, float t) {
	int extent = 2;
	return a + (b - a) * (1 - exp(extent * (-t)) / (1 - exp(-extent)));
}



