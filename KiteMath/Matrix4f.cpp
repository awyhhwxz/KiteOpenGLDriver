#include "stdafx.h"
#include "Matrix4f.h"
#include <memory>

namespace kite_math
{
	const Matrix4f Matrix4f::Identity = Matrix4f::scale(Vector3f(1, 1, 1));

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

	kite_math::Matrix4f Matrix4f::scale(const Vector3f& pos)
	{
		Matrix4f m;
		m._11 = pos.x;
		m._22 = pos.y;
		m._33 = pos.z;
		m._44 = 1;

		return m;
	}

	kite_math::Matrix4f Matrix4f::translate(const Vector3f& pos)
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

}