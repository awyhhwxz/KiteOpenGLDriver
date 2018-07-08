#include "stdafx.h"
#include "Vector3f.h"

namespace kite_math
{
	const Vector3f Vector3f::Right(1, 0, 0);
	const Vector3f Vector3f::Up(0, 1, 0);
	const Vector3f Vector3f::Forward(0, 0, 1);
	const Vector3f Vector3f::One(1.0f, 1.0f, 1.0f);
	const Vector3f Vector3f::Zero(0, 0, 0);

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