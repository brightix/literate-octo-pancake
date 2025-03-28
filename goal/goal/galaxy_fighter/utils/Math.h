#pragma once
namespace Math{

	float Lerp(float a, float b, float t);

	float SmoothStep(float t);

	float SmoothAcceleration();
	double SinInterpolation(float a, float b, float t);
	double CosInterpolation(float a, float b, float t);
	
	// a:��ʼֵ  b:����ֵ  t:(��ǰʱ��)/(��ʱ��)
	double ExpInterpolation(float a, float b, float t);	

}

