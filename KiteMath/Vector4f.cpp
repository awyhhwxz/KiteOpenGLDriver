#include "stdafx.h"
#include "Vector4f.h"

namespace kite_math
{
	Vector4f::Vector4f()
	{
	}


	Vector4f::Vector4f(float xVal, float yVal, float zVal, float wVal)
		: x(xVal), y(yVal), z(zVal), w(wVal)
	{

	}

	Vector4f::Vector4f(Vector3f v3, float wVal)
		: x(v3.x), y(v3.y), z(v3.z), w(wVal)
	{

	}

	Vector4f::~Vector4f()
	{
	}
}