#pragma once

namespace kite_driver
{
	class KITE_OPENGL_DRIVER_CORE_API IKiteDriverRenderItem
	{
	public:
		virtual void Initialize() = 0;
		virtual void Render() = 0;
	};
}