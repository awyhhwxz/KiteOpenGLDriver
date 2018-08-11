#include "stdafx.h"
#include "Ray.h"

namespace kite_math
{
	Ray::Ray()
	{
	}

	Ray::Ray(const Vector3f & origin, const Vector3f & direction)
		: _origin(origin), _direction(direction), _length(Mathf::kFloatMaxValue)
	{
	}

	Ray::Ray(const Vector3f & origin, const Vector3f & direction, float length)
		: _origin(origin), _direction(direction), _length(length)
	{
	}


	Ray::~Ray()
	{
	}

	bool Ray::CastPlane(const Plane& plane, float& distance)
	{
		const auto& normal = plane.get_normal();
	  	auto cos_normal_direct = Vector3f::Dot(normal, _direction);
		
		if (Mathf::Equal(cos_normal_direct, 0.0f))
		{
			return false;
		}
		else
		{
			auto t = (Vector3f::Dot(normal, plane.get_point()) - Vector3f::Dot(normal, _origin)) / cos_normal_direct;
			if (t < 0 || t > _length)
			{
				return false;
			}
			else
			{
				distance = t;
				return true;
			}
		}
	}
}