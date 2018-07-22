#include "stdafx.h"
#include "ImageLoader.h"
#include "FreeImage.h"

namespace kite_util
{
	KiteImageFormat ConvertToKiteImageFormat(FREE_IMAGE_TYPE image_type, FREE_IMAGE_COLOR_TYPE color_type)
	{
		switch (image_type)
		{
		case FIT_BITMAP:
			switch (color_type)
			{
			case FIC_RGB:
				return KiteImageFormat::KIF_BGR;
			}
			break;
		default:
			break;
		}

		return KIF_INVALID;
	}

	ImageLoader::ImageLoader()
	{
	}


	ImageLoader::ImageLoader(const tchar* file_path)
	{
		Load(file_path);
	}

	ImageLoader::~ImageLoader()
	{
	}

	bool ImageLoader::Load(const tchar * file_path)
	{	
		//image format
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		//pointer to the image, once loaded
		FIBITMAP *dib(0);
		//pointer to the image data
		BYTE* bits(0);
		//image width and height
		unsigned int width(0), height(0);

		//check the file signature and deduce its format
		fif = FreeImage_GetFileType(file_path, 0);
		//if still unknown, try to guess the file format from the file extension
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(file_path);	
		
		//if still unkown, return failure
		if (fif == FIF_UNKNOWN)
			return false;

		//check that the plugin has reading capabilities and load the file
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, file_path);
		//if the image failed to load, return failure
		if (!dib)
			return false;
			
		dib = FreeImage_ConvertTo24Bits(dib);

		//retrieve the image data
		bits = FreeImage_GetBits(dib);

		//get the image width and height
		_width = FreeImage_GetWidth(dib);
		_height = FreeImage_GetHeight(dib);

		_data_size = FreeImage_GetLine(dib) * _height;
		_data.reset(new uint8[_data_size]);
		memcpy(_data.get(), bits, _data_size);
		
		auto image_type = FreeImage_GetImageType(dib);
		auto color_type = FreeImage_GetColorType(dib);
		_image_format = ConvertToKiteImageFormat(image_type, color_type);

		//Free FreeImage's copy of the data
		FreeImage_Unload(dib);
		return true;
	}
}