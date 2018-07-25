#include "stdafx.h"
#include "KiteDriverRenderTexture.h"


namespace kite_driver
{
	KiteDriverRenderTexture::KiteDriverRenderTexture()
		: KiteDriverTexture()
	{
		_tex_target = GL_TEXTURE_2D;

		_width = 1024;
		_height = 1024;
		_image_format = kite_util::KIF_RGBA;
		this->SetGLData();
	}


	KiteDriverRenderTexture::~KiteDriverRenderTexture()
	{
	}

	void KiteDriverRenderTexture::SetWidthHeight(int width, int height)
	{
		KiteDriverTexture::SetWidthHeight(width, height);
		SetGLData();
	}

	void KiteDriverRenderTexture::SetImageFormat(kite_util::KiteImageFormat image_format)
	{
		KiteDriverTexture::SetImageFormat(image_format);
		SetGLData();
	}

	void KiteDriverRenderTexture::SetGLData()
	{
		glBindTexture(GL_TEXTURE_2D, _tex_id);

		SetTextureParameters();

		auto image_format = ConvertToGLImageFormat(_image_format);
		auto internal_image_format = ConvertToGLInternalImageFormat(_image_format);
		glTexImage2D(GL_TEXTURE_2D, 0, internal_image_format, _width, _height, 0, image_format, ParseGLDataType(_image_format), NULL);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

}