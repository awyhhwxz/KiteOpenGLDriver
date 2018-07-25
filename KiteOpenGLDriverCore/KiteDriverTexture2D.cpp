#include "stdafx.h"
#include "KiteDriverTexture2D.h"


namespace kite_driver
{
	KiteDriverTexture2D::KiteDriverTexture2D()
		: KiteDriverTexture()
	{
		_tex_target = GL_TEXTURE_2D;
	}


	KiteDriverTexture2D::~KiteDriverTexture2D()
	{
	}

	void KiteDriverTexture2D::Assign(kite_util::ImageLoader * loader)
	{
		SetPixels(loader->get_data(), loader->get_data_size());
		SetWidthHeight(loader->get_width(), loader->get_height());
		SetImageFormat(loader->get_image_format());
		SetGLData();
	}

	void KiteDriverTexture2D::SetPixels(uint8 * data, uint32 data_size)
	{
		_data.reset(new uint8[data_size]);
		memcpy(_data.get(), data, data_size);
	}



	void KiteDriverTexture2D::SetGLData()
	{
		glBindTexture(GL_TEXTURE_2D, _tex_id);

		SetTextureParameters();

		auto image_format = ConvertToGLImageFormat(_image_format);
		auto internal_image_format = ConvertToGLInternalImageFormat(_image_format);
		glTexImage2D(GL_TEXTURE_2D, 0, internal_image_format, _width, _height, 0, image_format, ParseGLDataType(_image_format), _data.get());
		
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}