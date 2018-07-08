#include "stdafx.h"
#include "KiteDriverDummy.h"

namespace kite_driver
{
	KiteDriverDummy::KiteDriverDummy()
		: _world(kite_math::Matrix4f::Identity)
	{
	}


	KiteDriverDummy::~KiteDriverDummy()
	{
	}
	void KiteDriverDummy::set_position(const kite_math::Vector3f & pos)
	{
		_pos = pos;
		RefreshWorldMatrix();
	}

	void KiteDriverDummy::RefreshWorldMatrix()
	{
		_world = kite_math::Matrix4f::translate(_pos);
	}

}