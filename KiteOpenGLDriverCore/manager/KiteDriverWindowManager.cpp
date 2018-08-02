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
		OnWindowSizeChanged();
	}

	void KiteDriverWindowManager::Refresh()
	{
		OnWindowSizeChanged();
	}

	void KiteDriverWindowManager::OnWindowSizeChanged()
	{
		WindowSizeChangedEvent.Invoke(_window_width, _window_height);
	}

}