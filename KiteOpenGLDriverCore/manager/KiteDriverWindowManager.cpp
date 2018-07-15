#include "stdafx.h"
#include "KiteDriverWindowManager.h"

namespace kite_driver
{
	KiteDriverWindowManager::KiteDriverWindowManager()
	{
	}


	KiteDriverWindowManager::~KiteDriverWindowManager()
	{
	}

	void KiteDriverWindowManager::SetWindowWidthAndHeight(float width, float height)
	{
		_window_width = width;
		_window_height = height;
		RefreshWindowCameraAspect();
	}

	void KiteDriverWindowManager::RefreshWindowCameraAspect()
	{
		if (_window_camera)
		{
			_window_camera->set_aspect(_window_width / _window_height);
		}
	}

}