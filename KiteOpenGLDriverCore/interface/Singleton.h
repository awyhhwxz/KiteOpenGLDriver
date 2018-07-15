#pragma once

namespace kite_driver
{
	template<class T> class Singleton
	{
	public:
		static T* Instance() { 
			if (_singleton == nullptr)
			{
				_singleton = new T();
			}

			return _singleton; 
		}

	protected:
		Singleton()
		{
		}
		
		static T* _singleton;
	};

	template<class T> T* Singleton<T>::_singleton = nullptr;
}