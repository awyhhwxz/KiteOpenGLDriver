#pragma once
namespace kite_math
{
	struct RayCastInfo
	{
	public:
		Vector3f Position;
		Vector3f TextureCoord;
		Vector3f BarycentricWeight;
		float Distance;
	};

	class KITE_MATH_API Ray
	{
	public:
		Ray();
		Ray(const Vector3f& origin, const Vector3f& direction);
		Ray(const Vector3f& origin, const Vector3f& direction, float length);
		~Ray();

		inline void set_origin(const Vector3f& origin) { _origin = origin; }
		inline const Vector3f& get_origin() { return _origin; }
		inline void set_direction(const Vector3f& direction) { _direction = direction; }
		inline const Vector3f& get_direction() { return _direction; }
		inline void set_length(float length) { _length = length; }
		inline float get_length() { return _length; }

		bool CastPlane(const Plane& plane, float& distance);
	private:
		Vector3f _origin;
		Vector3f _direction;
		float _length;
	};

}