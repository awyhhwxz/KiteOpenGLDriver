#pragma once

namespace kite_driver
{
	class ViewPort
	{
	public:
		ViewPort();
		ViewPort(int x, int y, int width, int height);
		ViewPort(const ViewPort& view_port);

		inline int get_x() const { return _x; }
		inline int get_y() const { return _y; }
		inline int get_width() const { return _width; }
		inline int get_height() const { return _height; }

	private:
		int _x;
		int _y;
		int _width;
		int _height;
	};
}