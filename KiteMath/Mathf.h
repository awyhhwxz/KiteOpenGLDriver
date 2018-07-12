#pragma once
namespace kite_math
{
	class KITE_MATH_API Mathf
	{
	public:

		static float Sin(float radian);
		static float SinDegree(float degree);
		static float Cos(float radian);
		static float CosDegree(float degree);
		static float Tan(float radian);
		static float TanDegree(float degree);
		static float DegreeToRad(float degree);

		const static float PI;
	};

}