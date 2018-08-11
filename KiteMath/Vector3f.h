#pragma once

namespace kite_math
{
	class KITE_MATH_API Vector3f
	{
	public:
		Vector3f();
		Vector3f(float xVal, float yVal, float zVal);
		Vector3f(const Vector2f& v2, float zVal);
		Vector3f(float vals[3]);
		Vector3f(float val);
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

		friend static Vector3f operator+(const Vector3f& v1, const Vector3f& v2)
		{
			return Vector3f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
		}

		friend static Vector3f operator-(const Vector3f& v1, const Vector3f& v2)
		{
			return Vector3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
		}

		friend static Vector3f operator*(const Vector3f& v1, float v2)
		{
			return Vector3f(v1.x * v2, v1.y * v2, v1.z * v2);
		}

		friend static Vector3f operator*(float v1, const Vector3f& v2)
		{
			return v2 * v1;
		}
		
		friend static Vector3f operator/(const Vector3f& v1, float v2)
		{
			return Vector3f(v1.x / v2, v1.y / v2, v1.z / v2);
		}

		static float Distance(const Vector3f& v) { return Mathf::Sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }
		static Vector3f Normalize(const Vector3f& v) { return v / Distance(v); }

		static float Dot(const Vector3f& v1, const Vector3f& v2)
		{
			return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
		}

		static Vector3f Cross(const Vector3f& v1, const Vector3f& v2)
		{
			return Vector3f(
				v1.y * v2.z - v1.z * v2.y
				, v1.z * v2.x - v1.x * v2.z
				, v1.x * v2.y - v1.y * v2.x);
		}
	};

}

