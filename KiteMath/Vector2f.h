#pragma once


namespace kite_math
{
	class KITE_MATH_API Vector2f
	{
	public:
		Vector2f();
		Vector2f(float xVal, float yVal);
		~Vector2f();

		union
		{
			float values[2];
			struct
			{
				float x, y;
			};
		};

		friend static Vector2f operator-(const Vector2f& v1, const Vector2f& v2)
		{
			return Vector2f(v1.x - v2.x, v1.y - v2.y);
		}

		friend static Vector2f operator/(const Vector2f& v1, float v2)
		{
			return Vector2f(v1.x / v2, v1.y / v2);
		}
	};
}
