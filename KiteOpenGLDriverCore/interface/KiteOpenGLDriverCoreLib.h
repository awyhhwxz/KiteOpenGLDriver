#pragma once

#ifdef KITEOPENGLDRIVERCORE_EXPORTS
#define KITE_OPENGL_DRIVER_CORE_API __declspec(dllexport)
#else
#define KITE_OPENGL_DRIVER_CORE_API __declspec(dllimport)
#endif 

#include "IKiteDriverRenderItem.h"
#include "IKiteDriverContext.h"
#include "KiteDriverShaderType.h"

namespace kite_driver
{
	KITE_OPENGL_DRIVER_CORE_API IKiteDriverContext* CreateKiteDriverContext();
	KITE_OPENGL_DRIVER_CORE_API void DestroyKiteDriverContext();
}