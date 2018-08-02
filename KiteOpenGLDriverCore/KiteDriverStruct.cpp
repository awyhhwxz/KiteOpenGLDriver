#include "stdafx.h"

namespace kite_driver
{
	ViewPort::ViewPort()
		: ViewPort(0, 0, 800, 600)
	{
	}

	ViewPort::ViewPort(int x, int y, int width, int height)
		: _x(x), _y(y), _width(width), _height(height)
	{
	}

	ViewPort::ViewPort(const ViewPort& view_port)
		:ViewPort(view_port._x, view_port._y, view_port._width, view_port._height)
	{

	}

}