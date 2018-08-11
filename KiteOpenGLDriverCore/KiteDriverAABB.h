#pragma once

namespace kite_driver
{
	class KiteDriverAABB
	{
	public:
		KiteDriverAABB();
		~KiteDriverAABB();

	public: 
		void Reset();
		void Extend(const kite_math::Vector3f& point);


		bool RayCast(kite_math::Ray ray);
	private:
		kite_math::Vector3f _min;
		kite_math::Vector3f _max;
	};
}

