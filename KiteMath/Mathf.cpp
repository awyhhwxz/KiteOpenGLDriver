#include "stdafx.h"
#include "Mathf.h"
#include <math.h>

namespace kite_math
{
	
	const float Mathf::PI = 3.14159265f;

	float Mathf::Sin(float radian)
	{
		return sin(radian);
	}
	float Mathf::SinDegree(float degree)
	{
		return Sin(DegreeToRad(degree));
	}
	float Mathf::Cos(float radian)
	{
		return cos(radian);
	}
	float Mathf::CosDegree(float degree)
	{
		return Cos(DegreeToRad(degree));
	}

	float Mathf::Tan(float radian)
	{
		return tan(radian);
	}

	float Mathf::TanDegree(float degree)
	{
		return Tan(DegreeToRad(degree));
	}

	float Mathf::DegreeToRad(float degree)
	{
		return degree / 180 * PI;
	}
}