#include "stdafx.h"
#include "KiteDriverContext.h"
#include "RenderItem/RenderItem01.h"

namespace kite_driver
{
	RenderItem01 renderitem01;
	IKiteDriverContext* g_kdc_context = nullptr;
	KITE_OPENGL_DRIVER_CORE_API IKiteDriverContext * kite_driver::CreateKiteDriverContext()
	{
		if (!g_kdc_context)
		{
			g_kdc_context = new KiteDriverContext;
			g_kdc_context->AddRenderItem(&renderitem01);
		}

		return g_kdc_context;
	}

	void DestroyKiteDriverContext()
	{
		if (g_kdc_context)
		{
			delete g_kdc_context;
			g_kdc_context = nullptr;
		}
	}
}