#include "stdafx.h"
#include "KiteDriverTextureCube.h"


namespace kite_driver
{
	KiteDriverTextureCube::KiteDriverTextureCube()
		: KiteDriverTexture()
	{
		_tex_target = GL_TEXTURE_CUBE_MAP;
	}


	KiteDriverTextureCube::~KiteDriverTextureCube()
	{
	}

	void KiteDriverTextureCube::Assign(kite_util::ImageLoader loaders[6])
	{
		for (int cube_index = 0; cube_index < 6; ++cube_index)
		{
			auto& loader = loaders[cube_index];
			if (cube_index == 0)
			{
				SetWidthHeight(loader.get_width(), loader.get_height());
				SetImageFormat(loader.get_image_format());
			}

			auto& data = _datas[cube_index];
			auto data_size = loader.get_data_size();
			data.reset(new uint8[data_size]);
			memcpy(data.get(), loader.get_data(), data_size);
		}

		SetGLData();
	}

	void KiteDriverTextureCube::SetGLData()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, _texId);

		SetTextureParameters();

		auto image_format = ConvertToGLImageFormat(_image_format);
		auto internal_image_format = ConvertToGLInternalImageFormat(_image_format);
		for (int cube_index = 0; cube_index < 6; ++cube_index)
		{
			auto& data = _datas[cube_index];
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + cube_index, 0, internal_image_format, _width, _height, 0, image_format, ParseGLDataType(_image_format), data.get());
		}
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
}