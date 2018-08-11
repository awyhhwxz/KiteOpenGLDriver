#pragma once
namespace kite_math
{
	class KITE_MATH_API Triangle
	{
	public:
		Triangle();
		~Triangle();

		static bool IsPointInTriangle(Vector3f triangle[3], const Vector3f& point, Vector3f& barycentric_weight);
		template<class T> static T ComputeDataViaBarycentric(T datas[3], const Vector3f& barycentric_weight)
		{
			return datas[0] * barycentric_weight.x + datas[1] * barycentric_weight.y + datas[2] * barycentric_weight.z;
		}
	};

}