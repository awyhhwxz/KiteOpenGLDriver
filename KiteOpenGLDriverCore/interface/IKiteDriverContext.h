#pragma once

namespace kite_driver
{
	class KITE_OPENGL_DRIVER_CORE_API IKiteDriverContext
	{
	public:
		virtual void Initialize(void* hwnd) = 0;
		virtual void AddRenderItem(IKiteDriverRenderItem* render_item) = 0;
		virtual void RemeveRenderItem(IKiteDriverRenderItem* render_item) = 0;
		virtual void Render() = 0;
		virtual void Resize(int width, int height) = 0;
	};
}