#pragma once

namespace kite_math
{
	class KITE_MATH_API Matrix4f
	{
	public:
		Matrix4f();
		Matrix4f(float val);
		Matrix4f(const Vector4f& col1,
			const Vector4f& col2, 
			const Vector4f& col3, 
			const Vector4f& col4);
		Matrix4f(const Matrix4f& m);
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

		void SetRows(const Vector4f& row0,
			const Vector4f& row1,
			const Vector4f& row2,
			const Vector4f& row3);

		void SetRow(int rowIndex, const Vector4f& row);
		Vector4f GetRow(int rowIndex) const;

		friend inline Matrix4f operator*(const Matrix4f& m1, const Matrix4f& m2)
		{
			Matrix4f m;
			m._11 = m1._11 * m2._11 + m1._12 * m2._21 + m1._13 * m2._31 + m1._14 * m2._41;
			m._12 = m1._11 * m2._12 + m1._12 * m2._22 + m1._13 * m2._32 + m1._14 * m2._42;
			m._13 = m1._11 * m2._13 + m1._12 * m2._23 + m1._13 * m2._33 + m1._14 * m2._43;
			m._14 = m1._11 * m2._14 + m1._12 * m2._24 + m1._13 * m2._34 + m1._14 * m2._44;

			m._21 = m1._21 * m2._11 + m1._22 * m2._21 + m1._23 * m2._31 + m1._24 * m2._41;
			m._22 = m1._21 * m2._12 + m1._22 * m2._22 + m1._23 * m2._32 + m1._24 * m2._42;
			m._23 = m1._21 * m2._13 + m1._22 * m2._23 + m1._23 * m2._33 + m1._24 * m2._43;
			m._24 = m1._21 * m2._14 + m1._22 * m2._24 + m1._23 * m2._34 + m1._24 * m2._44;

			m._31 = m1._31 * m2._11 + m1._32 * m2._21 + m1._33 * m2._31 + m1._34 * m2._41;
			m._32 = m1._31 * m2._12 + m1._32 * m2._22 + m1._33 * m2._32 + m1._34 * m2._42;
			m._33 = m1._31 * m2._13 + m1._32 * m2._23 + m1._33 * m2._33 + m1._34 * m2._43;
			m._34 = m1._31 * m2._14 + m1._32 * m2._24 + m1._33 * m2._34 + m1._34 * m2._44;

			m._41 = m1._41 * m2._11 + m1._42 * m2._21 + m1._43 * m2._31 + m1._44 * m2._41;
			m._42 = m1._41 * m2._12 + m1._42 * m2._22 + m1._43 * m2._32 + m1._44 * m2._42;
			m._43 = m1._41 * m2._13 + m1._42 * m2._23 + m1._43 * m2._33 + m1._44 * m2._43;
			m._44 = m1._41 * m2._14 + m1._42 * m2._24 + m1._43 * m2._34 + m1._44 * m2._44;

			return m;
		}

		friend inline Matrix4f operator*(const Matrix4f& m, const float fVal)
		{
			Matrix4f resultMat;
			for (int i = 0; i < 16; ++i)
			{
				resultMat.values[i] = m.values[i] * fVal;
			}
			return resultMat;
		}

		static const Matrix4f Identity;
	public:
		static Matrix4f Scale(const Vector3f& pos);
		static Matrix4f Translate(const Vector3f& pos);
		static Matrix4f Rotate(const Euler& euler);
		static Matrix4f Inverse(const Matrix4f& mat);
	};

}