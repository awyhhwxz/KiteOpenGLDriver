#include "stdafx.h"
#include "KiteDriverAABB.h"

namespace kite_driver
{
	KiteDriverAABB::KiteDriverAABB()
	{
	}


	KiteDriverAABB::~KiteDriverAABB()
	{
	}



	void KiteDriverAABB::Reset()
	{
		_min = kite_math::Vector3f(kite_math::Mathf::kFloatMaxValue);
		_max = kite_math::Vector3f(-kite_math::Mathf::kFloatMaxValue);
	}

	void KiteDriverAABB::Extend(const kite_math::Vector3f& point)
	{
		if (_min.x > point.x) _min.x = point.x;
		if (_min.y > point.y) _min.y = point.y;
		if (_min.z > point.z) _min.z = point.z;
		
		if (_max.x < point.x) _max.x = point.x;
		if (_max.y < point.y) _max.y = point.y;
		if (_max.z < point.z) _max.z = point.z;
	}

	bool KiteDriverAABB::RayCast(kite_math::Ray ray)
	{
		//Slabs method
		const auto origin = ray.get_origin();
		const auto direction = ray.get_direction();

		float max_val = kite_math::Mathf::kFloatMaxValue;
		float min_val = -kite_math::Mathf::kFloatMaxValue;

		for (int val_i = 0; val_i < 3; ++val_i)
		{
			if (kite_math::Mathf::Equal(direction.x, 0.0f))
			{
				if (origin.values[val_i] < _min.values[val_i] || origin.values[val_i] > _max.values[val_i])
				{
					return false;
				}
			}
			else
			{
				auto inv_dir = 1 / direction.values[val_i];
				auto t_min = (_min.values[val_i] - origin.values[val_i]) * inv_dir;
				auto t_max = (_max.values[val_i] - origin.values[val_i]) * inv_dir;

				if (t_max < t_min) kite_math::DataOperator<float>::Swap(t_min, t_max);

				if (t_max < max_val) max_val = t_max;
				if (t_min > min_val) min_val = t_min;

				if (min_val > max_val) return false;
			}
		}

		return true;
	}

}
