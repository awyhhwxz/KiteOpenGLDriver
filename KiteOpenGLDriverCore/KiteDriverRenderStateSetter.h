#pragma once

namespace kite_driver
{
	class KiteDriverRenderStateSetter
	{
	public:
		KiteDriverRenderStateSetter();
		~KiteDriverRenderStateSetter();

	public:
		void SetZWriteEnable(bool enable);

		void StateSet();
	private:
		bool _enable_zwrite;
	};
}