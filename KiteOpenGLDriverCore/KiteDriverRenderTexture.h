#pragma once

namespace kite_driver
{
	class KiteDriverRenderTexture : public KiteDriverTexture
	{
	public:
		KiteDriverRenderTexture();
		~KiteDriverRenderTexture();

		virtual void SetWidthHeight(int width, int height) override;
		virtual void SetImageFormat(kite_util::KiteImageFormat image_format) override;

		GLuint get_gl_tex_id() { return _tex_id; }
	protected:
		virtual void SetGLData() override;
	};

	typedef std::shared_ptr<KiteDriverRenderTexture> KiteDriverRenderTexturePtr;
}