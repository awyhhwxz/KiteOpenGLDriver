#pragma once

namespace kite_math
{
	class KITE_MATH_API Vector3f
	{
	public:
		Vector3f();
		Vector3f(float xVal, float yVal, float zVal);
		~Vector3f();

		union
		{
			float values[3];
			struct
			{
				float x, y, z;
			};
		};

		static const Vector3f Right;
		static const Vector3f Up;
		static const Vector3f Forward;
		static const Vector3f One;
		static const Vector3f Zero;
	};

}

