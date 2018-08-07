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
		static float ZeroOneToPNOne(float val);
		static float Sqrt(float val);
		static float Abs(float val);
		static bool Equal(float val1, float val2);
		const static float PI;
		const static float kFloatPrecision;
		const static float kFloatMaxValue;
	};

}