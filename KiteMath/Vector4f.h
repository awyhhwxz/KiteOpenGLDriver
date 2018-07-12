#pragma once
namespace kite_math
{
	class KITE_MATH_API Vector4f
	{
	public:
		Vector4f();
		Vector4f(float xVal, float yVal, float zVal, float wVal);
		Vector4f(Vector3f v3, float wVal);
		~Vector4f();		
		
		union
		{
			float values[4];
			struct
			{
				float x, y, z, w;
			};
		};

		friend inline Vector4f operator*(const Vector4f& v1, const Vector4f& v2)
		{
			return Vector4f(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
		}

		friend inline Vector4f operator+(const Vector4f& v1, const Vector4f& v2)
		{
			return Vector4f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
		}

		friend inline Vector4f operator-(const Vector4f& v1, const Vector4f& v2)
		{
			return Vector4f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
		}
	};

}