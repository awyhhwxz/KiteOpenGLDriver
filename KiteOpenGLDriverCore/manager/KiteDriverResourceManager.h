#pragma once

namespace kite_driver
{
	class KiteDriverResourceManager : public Singleton<KiteDriverResourceManager>
	{
	public:
		KiteDriverResourceManager();
		~KiteDriverResourceManager();
	};

}