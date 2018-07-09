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

	Matrix4f::~Matrix4f()
	{
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


}