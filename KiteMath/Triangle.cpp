#include "stdafx.h"
#include "Triangle.h"

namespace kite_math
{
	Triangle::Triangle()
	{
	}


	Triangle::~Triangle()
	{
	}

	bool Triangle::IsPointInTriangle(Vector3f triangle[3], const Vector3f & point, Vector3f& centroid_weight)
	{
		auto r = point - triangle[0];
		auto q1 = triangle[1] - triangle[0];
		auto q2 = triangle[2] - triangle[0];

		auto q1_square = Vector3f::Dot(q1, q1);
		auto q2_square = Vector3f::Dot(q2, q2);
		auto q1_q2 = Vector3f::Dot(q1, q2);
		auto r_q1 = Vector3f::Dot(r, q1);
		auto r_q2 = Vector3f::Dot(r, q2);

		auto det = 1.0f / (q1_square * q2_square - q1_q2 * q1_q2);
		auto omega1 = det * (q2_square * r_q1 - q1_q2 * r_q2);
		auto omega2 = det * (q1_square * r_q2 - q1_q2 * r_q1);
		auto omega0 = 1 - omega1 - omega2;

		if (omega0 >= 0 && omega1 >= 0 && omega2 >= 0)
		{
			centroid_weight.x = omega0;
			centroid_weight.y = omega1;
			centroid_weight.z = omega2;
			return true;
		}
		else
		{
			return false;
		}
	}
}