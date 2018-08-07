#include "stdafx.h"
#include "KiteDriverDummy.h"

namespace kite_driver
{
	KiteDriverDummy::KiteDriverDummy()
		: KiteDriverBaseObject()
		, _world(kite_math::Matrix4f::Identity)
		, _inverse_world(kite_math::Matrix4f::Identity)
		, _scale(kite_math::Vector3f::One)
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

	void KiteDriverDummy::set_euler(const kite_math::Euler & euler)
	{
		_euler = euler;
		RefreshWorldMatrix();
	}

	void KiteDriverDummy::set_scale(const kite_math::Vector3f & scale)
	{
		_scale = scale;
		RefreshWorldMatrix();
	}

	void KiteDriverDummy::Translate(const kite_math::Vector3f & translate)
	{
		auto translatefinal = kite_math::Matrix4f::Rotate(_euler) * translate;
		set_position(_pos + translatefinal);
	}

	kite_driver::KiteDriverObjectType KiteDriverDummy::get_type()
	{
		return KiteDriverObjectType::KDOT_DUMMY;
	}

	void KiteDriverDummy::RefreshWorldMatrix()
	{
		_world = kite_math::Matrix4f::Translate(_pos) * kite_math::Matrix4f::Rotate(_euler) * kite_math::Matrix4f::Scale(_scale);
		_inverse_world = kite_math::Matrix4f::Inverse(_world);
	}

}