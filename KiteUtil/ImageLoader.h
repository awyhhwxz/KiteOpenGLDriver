#pragma once

#include "kite_driver_typedef.h"
namespace kite_util
{
	enum KiteImageFormat
	{
		KIF_INVALID,
		KIF_RGBA,
		KIF_RGB,
		KIF_BGR,
	};

	class KITE_UTIL_API ImageLoader
	{
	public:
		ImageLoader();
		ImageLoader(const tchar* file_path);
		~ImageLoader();

	public: 
		bool Load(const tchar* file_path);
		inline const uint32 get_width() { return _width; }
		inline const uint32 get_height() { return _height; }
		inline const uint32 get_data_size() { return _data_size; }
		uint8* get_data() { return _data.get(); }
		inline const KiteImageFormat get_image_format() { return _image_format; }
	private:
		std::unique_ptr<uint8[]> _data;
		uint32 _data_size;
		uint32 _width;
		uint32 _height;
		KiteImageFormat _image_format;
	};
}

