#pragma once
namespace kite_math
{
	class KITE_MATH_API Vector4f
	{
	public:
		Vector4f();
		Vector4f(float xVal, float yVal, float zVal, float wVal);
		Vector4f(Vector3f v3, float wVal);
		~Vector4f();		
		
		union
		{
			float values[4];
			struct
			{
				float x, y, z, w;
			};
		};
	};

}