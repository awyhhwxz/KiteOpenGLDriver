#pragma once


namespace kite_driver
{
	class KiteDriverDummy
	{
	public:
		KiteDriverDummy();
		~KiteDriverDummy();

	public:
		void set_position(const kite_math::Vector3f& pos);
		const kite_math::Matrix4f& get_world_matrix() { return _world; }

	protected:
		virtual void RefreshWorldMatrix();

	protected:
		
		kite_math::Vector3f _pos;
		kite_math::Matrix4f _world;
	};

}