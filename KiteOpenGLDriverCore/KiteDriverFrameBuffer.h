#pragma once


namespace kite_driver
{
	class KiteDriverFrameBuffer
	{
	public:
		KiteDriverFrameBuffer();
		~KiteDriverFrameBuffer();

		void BeginRender();
		void EndRender();

		void SetRenderTarget(const KiteDriverRenderTexturePtr& render_target);
		const KiteDriverRenderTexturePtr& GetRenderTarget();

		void set_view_port(const ViewPort& view_port) { _view_port = view_port; }
	protected:
		KiteDriverRenderTexturePtr _render_target;
		GLuint _fbo;
		GLuint _depth_id;

		void GenerateFBO();

	private: 
		ViewPort _view_port;
		bool _fbo_is_init;

	};

	typedef std::shared_ptr<KiteDriverFrameBuffer> KiteDriverFrameBufferPtr;
}

