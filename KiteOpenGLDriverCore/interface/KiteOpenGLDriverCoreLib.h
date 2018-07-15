#pragma once

#ifdef KITEOPENGLDRIVERCORE_EXPORTS
#define KITE_OPENGL_DRIVER_CORE_API __declspec(dllexport)
#else
#define KITE_OPENGL_DRIVER_CORE_API __declspec(dllimport)
#endif 


#include <vector>
#include <memory>

#include "KiteMathLib.h"

#include "kite_driver_typedef.h"
#include "IKiteDriverRenderItem.h"
#include "IKiteDriverContext.h"
#include "KiteDriverShaderType.h"

#include "IMouseMessageReceiver.h"

#include "Singleton.h"
#include "KiteDriverInputManager.h"

namespace kite_driver
{
	KITE_OPENGL_DRIVER_CORE_API IKiteDriverContext* CreateKiteDriverContext();
	KITE_OPENGL_DRIVER_CORE_API void DestroyKiteDriverContext();
}