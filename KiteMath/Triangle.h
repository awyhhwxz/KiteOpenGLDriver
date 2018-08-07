#pragma once
namespace kite_math
{
	class KITE_MATH_API Triangle
	{
	public:
		Triangle();
		~Triangle();

		static bool IsPointInTriangle(Vector3f triangle[3], const Vector3f& point, Vector3f& centroid_weight);
	};

}