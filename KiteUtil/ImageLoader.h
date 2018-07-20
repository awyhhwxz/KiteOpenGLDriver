#pragma once

#include "kite_driver_typedef.h"
namespace kite_util
{
	enum KiteImageFormat
	{
		KIF_INVALID,
		KIF_RGB,
	};

	class KITE_UTIL_API ImageLoader
	{
	public:
		ImageLoader();
		~ImageLoader();

	public: 
		bool Load(const tchar* file_path);
		inline uint32 get_width() { return _width; }
		inline uint32 get_height() { return _height; }
		inline uint32 get_data_size() { return _data_size; }
		uint8* get_data() { return _data.get(); }
		KiteImageFormat get_image_format() { return _image_format; }
	private:
		std::unique_ptr<uint8[]> _data;
		uint32 _data_size;
		uint32 _width;
		uint32 _height;
		KiteImageFormat _image_format;
	};
}

