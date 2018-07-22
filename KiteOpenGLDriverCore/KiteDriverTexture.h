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

		virtual void SetWidthHeight(float width, float height);
		virtual void SetImageFormat(kite_util::KiteImageFormat image_format);

	protected:
		GLint ConvertToGLImageFormat(kite_util::KiteImageFormat kite_image_format);
		GLint ConvertToGLInternalImageFormat(kite_util::KiteImageFormat kite_image_format);
		GLenum ParseGLDataType(kite_util::KiteImageFormat kite_image_format);
		void SetTextureParameters();

	protected:
		GLuint _texId;
		GLenum _tex_target;
		
		float _width;
		float _height;
		kite_util::KiteImageFormat _image_format;
	};


}