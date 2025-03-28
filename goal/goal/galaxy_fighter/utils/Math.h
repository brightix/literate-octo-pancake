#pragma once
namespace Math{

	float Lerp(float a, float b, float t);

	float SmoothStep(float t);

	float SmoothAcceleration();
	double SinInterpolation(float a, float b, float t);
	double CosInterpolation(float a, float b, float t);
	
	// a:初始值  b:最终值  t:(当前时间)/(总时间)
	double ExpInterpolation(float a, float b, float t);	

}

