#pragma once

namespace kite_driver
{
	class KiteDriverTexture2D
	{
	public:
		KiteDriverTexture2D();
		~KiteDriverTexture2D();

	public:

		void Assign(kite_util::ImageLoader* loader);
		void SetPixels(uint8* data, uint32 data_size);
		void SetWidthHeight(float width, float height);
		void SetImageFormat(kite_util::KiteImageFormat image_format);

		void BindTexture();
		void UnbindTexture();
	private:
		void SetGLData();
		GLint ConvertToGLImageFormat(kite_util::KiteImageFormat kite_image_format);
		GLenum ParseGLDataType(kite_util::KiteImageFormat kite_image_format);

	private:
		std::unique_ptr<uint8[]> _data;
		float _width;
		float _height;
		kite_util::KiteImageFormat _image_format;
	private: 
		GLuint _texId;

	};

}