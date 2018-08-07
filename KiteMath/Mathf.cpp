#include "stdafx.h"
#include "Mathf.h"
#include <math.h>

namespace kite_math
{
	
	const float Mathf::PI = 3.14159265f;
	const float Mathf::kFloatPrecision = 1.0e-6f;
	const float Mathf::kFloatMaxValue = 0x7fffffff;

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
	float Mathf::ZeroOneToPNOne(float val)
	{
		return val * 2.0f - 1.0f;
	}

	float Mathf::Sqrt(float val)
	{
		return sqrt(val);
	}

	float Mathf::Abs(float val)
	{
		return val < 0 ? -val : val;
	}

	bool Mathf::Equal(float val1, float val2)
	{
		return Abs(val1 - val2) < kFloatPrecision;
	}

}