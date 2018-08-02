#pragma once

#include "KiteDriverTempObjectGetter.h"

namespace kite_driver
{
	class KiteDriverShareObjectManager : public Singleton<KiteDriverShareObjectManager>
	{
	public:
		KiteDriverShareObjectManager();
		~KiteDriverShareObjectManager();

		KiteDriverMeshDrawer* get_fullscreen_plane();
		KiteDriverMaterialPtr get_texture_material();
		KiteDriverFrameBufferPtr GetTemporaryFrameBuffer();
		void ReleaseTemporaryFrameBuffer(const KiteDriverFrameBufferPtr& frame_buffer);
		KiteDriverRenderTexturePtr GetTemporaryRenderTexture();
		void ReleaseTemporaryRenderTexture(const KiteDriverRenderTexturePtr& render_texture);

	private:
		void InitializeFullScreenPlane();
		void InitializeTextureMaterial();
		void InitializeShareFrameBuffer();
	private:
		KiteDriverMaterialPtr _texture_material;
		KiteDriverMeshDrawerPtr _fullscreen_plane_drawer;

		KiteDriverTempObjectGetter<KiteDriverFrameBuffer> _temp_framebuffer_getter;
		KiteDriverTempObjectGetter<KiteDriverRenderTexture> _temp_rendertexture_getter;
	};
}
