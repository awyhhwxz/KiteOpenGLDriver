#pragma once
namespace kite_math
{
	class KITE_MATH_API Euler
	{
	public:
		Euler();
		Euler(float pitchRad, float yawRad, float rollRad);
		~Euler();

		union
		{
			float values[3];
			struct
			{
				float pitch, yaw, roll;
				float x, y, z;
			};
		};

		void SetDegree(float pitchDegree, float yawDegree, float rollDegree);
	};

}