#include "stdafx.h"
#include "Matrix4f.h"
#include <memory>

namespace kite_math
{
	const Matrix4f Matrix4f::Identity = Matrix4f::Scale(Vector3f(1, 1, 1));

	Matrix4f::Matrix4f()
		: Matrix4f(0)
	{
	}


	Matrix4f::Matrix4f(float val)
	{
		memset(values, 0, sizeof(float) * 16);
	}

	Matrix4f::Matrix4f(const Vector4f& col1, const Vector4f& col2, const Vector4f& col3, const Vector4f& col4)
	{
		cols[0] = col1;
		cols[1] = col2;
		cols[2] = col3;
		cols[3] = col4;
	}

	Matrix4f::Matrix4f(const Matrix4f& m)
	{
		memcpy(this->values, m.values, sizeof(float) * 16);
	}

	Matrix4f::~Matrix4f()
	{
	}
	
	void Matrix4f::SetRows(const Vector4f& row0, const Vector4f& row1, const Vector4f& row2, const Vector4f& row3)
	{
		SetRow(0, row0);
		SetRow(1, row1);
		SetRow(2, row2);
		SetRow(3, row3);
	}

	void Matrix4f::SetRow(int rowIndex, const Vector4f & row)
	{
		for (int i = 0; i < 4; ++i)
		{
			values[i * 4 + rowIndex] = row.values[i];
		}
	}

	kite_math::Vector4f Matrix4f::GetRow(int rowIndex) const
	{
		Vector4f v;
		for (int i = 0 ; i < 4 ; ++i)
		{
			v.values[i] = values[i * 4 + rowIndex];
		}
		return v;
	}

	kite_math::Matrix4f Matrix4f::Scale(const Vector3f& pos)
	{
		Matrix4f m;
		m._11 = pos.x;
		m._22 = pos.y;
		m._33 = pos.z;
		m._44 = 1;

		return m;
	}

	kite_math::Matrix4f Matrix4f::Translate(const Vector3f& pos)
	{
		Matrix4f m;
		m._11 = 1;
		m._22 = 1;
		m._33 = 1;
		m._44 = 1;

		m._14 = pos.x;
		m._24 = pos.y;
		m._34 = pos.z;

		return m;
	}

	Matrix4f Matrix4f::Rotate(const Euler & euler)
	{
		float cospitch = Mathf::Cos(euler.pitch),
			sinpitch = Mathf::Sin(euler.pitch),
			cosyaw = Mathf::Cos(euler.yaw),
			sinyaw = Mathf::Sin(euler.yaw),
			cosroll = Mathf::Cos(euler.roll),
			sinroll = Mathf::Sin(euler.roll);


		Matrix4f m;
		m._11 = cosroll * cosyaw;	m._12 = cosroll * sinyaw * sinpitch - sinroll * cospitch;	m._13 = cosroll * sinyaw * cospitch + sinroll * sinpitch;
		m._21 = sinroll * cosyaw;	m._22 = sinroll * sinyaw * sinpitch + cosroll * cospitch;	m._23 = sinroll * sinyaw * cospitch - cosroll * sinpitch;
		m._31 = -sinyaw;			m._32 = cosyaw * sinpitch;									m._33 = cosyaw * cospitch;

		m._44 = 1;
		return m;
	}

	Matrix4f Matrix4f::Inverse(const Matrix4f & mat)
	{
		float Coef00 = mat._33 * mat._44 - mat._43 * mat._34;
		float Coef02 = mat._23 * mat._44 - mat._43 * mat._24;
		float Coef03 = mat._23 * mat._34 - mat._33 * mat._24;		
		float Coef04 = mat._32 * mat._44 - mat._42 * mat._34;
		float Coef06 = mat._22 * mat._44 - mat._42 * mat._24;
		float Coef07 = mat._22 * mat._34 - mat._32 * mat._24;		
		float Coef08 = mat._32 * mat._43 - mat._42 * mat._33;
		float Coef10 = mat._22 * mat._43 - mat._42 * mat._23;
		float Coef11 = mat._22 * mat._33 - mat._32 * mat._23;		
		float Coef12 = mat._31 * mat._44 - mat._41 * mat._34;
		float Coef14 = mat._21 * mat._44 - mat._41 * mat._24;
		float Coef15 = mat._21 * mat._34 - mat._31 * mat._24;		
		float Coef16 = mat._31 * mat._43 - mat._41 * mat._33;
		float Coef18 = mat._21 * mat._43 - mat._41 * mat._23;
		float Coef19 = mat._21 * mat._33 - mat._31 * mat._23;		
		float Coef20 = mat._31 * mat._42 - mat._41 * mat._32;
		float Coef22 = mat._21 * mat._42 - mat._41 * mat._22;
		float Coef23 = mat._21 * mat._32 - mat._31 * mat._22;

		Vector4f Fac0(Coef00, Coef00, Coef02, Coef03);
		Vector4f Fac1(Coef04, Coef04, Coef06, Coef07);
		Vector4f Fac2(Coef08, Coef08, Coef10, Coef11);
		Vector4f Fac3(Coef12, Coef12, Coef14, Coef15);
		Vector4f Fac4(Coef16, Coef16, Coef18, Coef19);
		Vector4f Fac5(Coef20, Coef20, Coef22, Coef23);

		Vector4f Vec0(mat._21, mat._11, mat._11, mat._11);
		Vector4f Vec1(mat._22, mat._12, mat._12, mat._12);
		Vector4f Vec2(mat._23, mat._13, mat._13, mat._13);
		Vector4f Vec3(mat._24, mat._14, mat._14, mat._14);
		
		Vector4f Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
		Vector4f Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
		Vector4f Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
		Vector4f Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);
		
		Vector4f SignA(+1, -1, +1, -1);
		Vector4f SignB(-1, +1, -1, +1);

		Matrix4f Inverse;
		Inverse.SetRows(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

		Vector4f Row0(Inverse._11, Inverse._21, Inverse._31, Inverse._41);

		Vector4f Dot0(mat.GetRow(0) * Row0);
		float Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

		float OneOverDeterminant = static_cast<float>(1) / Dot1;

		return Inverse * OneOverDeterminant;
	}


}