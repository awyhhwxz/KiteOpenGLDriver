#pragma once


namespace kite_driver
{
	class KiteDriverFrameBuffer
	{
	public:
		KiteDriverFrameBuffer();
		~KiteDriverFrameBuffer();

		void BeginRender(KiteDriverCamera* camera);
		void EndRender();

		void SetRenderTarget(const KiteDriverRenderTexturePtr& render_target);

	private:
		KiteDriverRenderTexturePtr _render_target;
		GLuint _fbo;
		GLuint _depth_id;

	};
}

