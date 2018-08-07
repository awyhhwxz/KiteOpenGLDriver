#include "stdafx.h"
#include "Plane.h"

namespace kite_math
{
	Plane::Plane()
	{
	}

	Plane::Plane(const Vector3f & point, const Vector3f & normal)
		: _point(point), _normal(normal)
	{
	}

	Plane::Plane(Vector3f points[3])
	{
		_point = points[0];
		_normal = Vector3f::Cross(points[2] - points[0], points[1] - points[0]);
	}


	Plane::~Plane()
	{
	}
}