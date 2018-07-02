#pragma once

namespace kite_math
{
	class KITE_MATH_API Vector3f
	{
	public:
		Vector3f();
		Vector3f(float x, float y, float z);
		~Vector3f();

		union
		{
			float values[3];
			struct
			{
				float x, y, z;
			};
		};

		float* operator ()()
		{
			return values;
		}
	};

}

