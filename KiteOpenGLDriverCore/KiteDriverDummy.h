#pragma once


namespace kite_driver
{
	class KiteDriverDummy : public KiteDriverBaseObject
	{
	public:
		KiteDriverDummy();
		~KiteDriverDummy();

	public:
		virtual KiteDriverObjectType get_type() override;

	public:
		void set_position(const kite_math::Vector3f& pos);
		const kite_math::Vector3f& get_position() { return _pos; }
		void set_euler(const kite_math::Euler& euler);
		void set_scale(const kite_math::Vector3f& scale);
		const kite_math::Matrix4f& get_world_matrix() { return _world; }
		const kite_math::Matrix4f& get_inverse_world_matrix() { return _inverse_world; }

		void Translate(const kite_math::Vector3f& translate);
	protected:
		virtual void RefreshWorldMatrix();

	protected:
		
		kite_math::Vector3f _pos;
		kite_math::Euler _euler;
		kite_math::Vector3f _scale;
		kite_math::Matrix4f _world;
		kite_math::Matrix4f _inverse_world;
	};

}