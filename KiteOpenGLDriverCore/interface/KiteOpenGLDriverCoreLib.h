#pragma once

#ifdef KITEOPENGLDRIVERCORE_EXPORTS
#define KITE_OPENGL_DRIVER_CORE_API __declspec(dllexport)
#else
#define KITE_OPENGL_DRIVER_CORE_API __declspec(dllimport)
#endif 


#include <vector>
#include <stack>
#include <memory>
#include <functional>
#include "KiteDriverEvent.h"
#include "KiteDriverObjectType.h"

#include "kite_driver_typedef.h"
#include "KiteMathLib.h"

#include "IKiteDriverRenderItem.h"
#include "IKiteDriverContext.h"
#include "KiteDriverShaderType.h"

#include "IMouseMessageReceiver.h"

#include "Singleton.h"
#include "KiteDriverInputManager.h"
#include "KiteDriverResourceManager.h"

namespace kite_driver
{
	KITE_OPENGL_DRIVER_CORE_API IKiteDriverContext* CreateKiteDriverContext();
	KITE_OPENGL_DRIVER_CORE_API void DestroyKiteDriverContext();
}