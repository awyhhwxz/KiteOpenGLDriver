#include "stdafx.h"
#include "KiteDriverTexture2D.h"


namespace kite_driver
{
	KiteDriverTexture2D::KiteDriverTexture2D()
	{
		glGenTextures(1, &_texId);
	}


	KiteDriverTexture2D::~KiteDriverTexture2D()
	{
		glDeleteTextures(1, &_texId);
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

	void KiteDriverTexture2D::SetWidthHeight(float width, float height)
	{
		_width = width;
		_height = height;
	}

	void KiteDriverTexture2D::SetImageFormat(kite_util::KiteImageFormat image_format)
	{
		_image_format = image_format;
	}

	void KiteDriverTexture2D::BindTexture()
	{
		glBindTexture(GL_TEXTURE_2D, _texId);
	}

	void KiteDriverTexture2D::UnbindTexture()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void KiteDriverTexture2D::SetGLData()
	{
		glBindTexture(GL_TEXTURE_2D, _texId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		auto image_format = ConvertToGLImageFormat(_image_format);
		glTexImage2D(GL_TEXTURE_2D, 0, image_format, _width, _height, 0, image_format, ParseGLDataType(_image_format), _data.get());
		
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLint KiteDriverTexture2D::ConvertToGLImageFormat(kite_util::KiteImageFormat kite_image_format)
	{
		switch (kite_image_format)
		{
		case kite_util::KIF_INVALID:
			break;
		case kite_util::KIF_RGB:
			return GL_RGB;
		default:
			break;
		}
		return -1;
	}

	GLenum KiteDriverTexture2D::ParseGLDataType(kite_util::KiteImageFormat kite_image_format)
	{
		switch (kite_image_format)
		{
		case kite_util::KIF_INVALID:
			break;
		case kite_util::KIF_RGB:
			return GL_UNSIGNED_BYTE;
		default:
			break;
		}
		return -1;
	}

}