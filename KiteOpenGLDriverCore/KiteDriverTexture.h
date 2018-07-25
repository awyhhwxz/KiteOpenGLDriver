#pragma once

namespace kite_driver
{
	class KiteDriverTexture
	{
	public:
		KiteDriverTexture();
		~KiteDriverTexture();

		void BindTexture();
		void UnbindTexture();

		virtual void SetWidthHeight(int width, int height);
		virtual void SetImageFormat(kite_util::KiteImageFormat image_format);

		inline float get_width() { return _width; }
		inline float get_height() { return _height; }
	protected:

		virtual void SetGLData() = 0;

		GLint ConvertToGLImageFormat(kite_util::KiteImageFormat kite_image_format);
		GLint ConvertToGLInternalImageFormat(kite_util::KiteImageFormat kite_image_format);
		GLenum ParseGLDataType(kite_util::KiteImageFormat kite_image_format);
		void SetTextureParameters();

	protected:
		GLuint _tex_id;
		GLenum _tex_target;
		
		int _width;
		int _height;
		kite_util::KiteImageFormat _image_format;
	};


}