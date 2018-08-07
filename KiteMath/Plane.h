#pragma once
namespace kite_math
{
	class KITE_MATH_API Plane
	{
	public:
		Plane();
		Plane(const Vector3f& point, const Vector3f& normal);
		Plane(Vector3f points[3]);
		~Plane();

	public:
		inline const Vector3f& get_normal() const { return _normal; }
		inline const Vector3f& get_point() const { return _point; }
	private:
		Vector3f _normal;
		Vector3f _point;
	};

}