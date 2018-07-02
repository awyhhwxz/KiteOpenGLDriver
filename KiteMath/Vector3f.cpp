#include "stdafx.h"
#include "Vector3f.h"

namespace kite_math
{
	Vector3f::Vector3f()
		: Vector3f(0, 0, 0)
	{
	}

	Vector3f::Vector3f(float xVal, float yVal, float zVal)
		: x(xVal), y(yVal), z(zVal)
	{
	}


	Vector3f::~Vector3f()
	{
	}
}