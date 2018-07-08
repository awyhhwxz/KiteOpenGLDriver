#pragma once

namespace kite_math
{
	class KITE_MATH_API Matrix4f
	{
	public:
		Matrix4f();
		Matrix4f(float val);
		~Matrix4f();

		union
		{
			float values[16];
			struct
			{
				float _11, _21, _31, _41,
					_12, _22, _32, _42,
					_13, _23, _33, _43,
					_14, _24, _34, _44;
			};

			Vector4f cols[4];
		};

		static const Matrix4f Identity;
	public:
		static Matrix4f scale(const Vector3f& pos);
		static Matrix4f translate(const Vector3f& pos);
	};

}