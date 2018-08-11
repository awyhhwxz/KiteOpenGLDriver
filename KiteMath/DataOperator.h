#pragma once
namespace kite_math
{
	template<class T> class DataOperator
	{
	public:
		static void Swap(T& v1, T& v2)
		{
			T temp = v1;
			v1 = v2;
			v2 = temp;
		}
	};
}
