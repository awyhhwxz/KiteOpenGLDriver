#include "stdafx.h"
#include "KiteDriverTexture.h"

namespace kite_driver
{
	KiteDriverTexture::KiteDriverTexture()
	{
		glGenTextures(1, &_tex_id);
	}


	KiteDriverTexture::~KiteDriverTexture()
	{
		glDeleteTextures(1, &_tex_id);
	}

	void KiteDriverTexture::BindTexture()
	{
		glBindTexture(_tex_target, _tex_id);
	}

	void KiteDriverTexture::UnbindTexture()
	{
		glBindTexture(_tex_target, 0);
	}

	void KiteDriverTexture::SetWidthHeight(int width, int height)
	{
		_width = width;
		_height = height;
	}

	void KiteDriverTexture::SetImageFormat(kite_util::KiteImageFormat image_format)
	{
		_image_format = image_format;
	}

	GLint KiteDriverTexture::ConvertToGLImageFormat(kite_util::KiteImageFormat kite_image_format)
	{
		switch (kite_image_format)
		{
		case kite_util::KIF_INVALID:
			break;
		case kite_util::KIF_RGB:
			return GL_RGB;
		case kite_util::KIF_RGBA:
			return GL_RGBA;
		case kite_util::KIF_BGR:
			return GL_BGR;
		default:
			break;
		}
		return -1;
	}

	GLint KiteDriverTexture::ConvertToGLInternalImageFormat(kite_util::KiteImageFormat kite_image_format)
	{
		switch (kite_image_format)
		{
		case kite_util::KIF_INVALID:
			break;
		case kite_util::KIF_RGB:
		case kite_util::KIF_BGR:
			return GL_RGB;
		case kite_util::KIF_RGBA:
			return GL_RGBA;
		default:
			break;
		}
		return -1;
	}

	GLenum KiteDriverTexture::ParseGLDataType(kite_util::KiteImageFormat kite_image_format)
	{
		switch (kite_image_format)
		{
		case kite_util::KIF_INVALID:
			break;
		case kite_util::KIF_RGB:
		case kite_util::KIF_BGR:
			return GL_UNSIGNED_BYTE;
		case kite_util::KIF_RGBA:
			return GL_UNSIGNED_BYTE;
		default:
			break;
		}
		return -1;
	}

	void KiteDriverTexture::SetTextureParameters()
	{
		glTexParameteri(_tex_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(_tex_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(_tex_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(_tex_target, GL_TEXTURE_WRAP_T, GL_REPEAT);

	}

}