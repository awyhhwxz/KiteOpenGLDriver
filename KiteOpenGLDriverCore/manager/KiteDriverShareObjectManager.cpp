#include "stdafx.h"
#include "KiteDriverShareObjectManager.h"
#include "KiteDriverGeometryGenerator.h"
#include "KiteDriverFastAccess.h"

namespace kite_driver
{
	KiteDriverShareObjectManager::KiteDriverShareObjectManager()
	{
	}


	KiteDriverShareObjectManager::~KiteDriverShareObjectManager()
	{
	}

	kite_driver::KiteDriverMeshDrawer* KiteDriverShareObjectManager::get_fullscreen_plane()
	{
		if (!_fullscreen_plane_drawer)
		{
			InitializeFullScreenPlane();
		}

		return _fullscreen_plane_drawer.get();
	}

	KiteDriverMaterialPtr KiteDriverShareObjectManager::get_texture_material()
	{
		if (!_texture_material)
		{
			InitializeTextureMaterial();
		}

		return _texture_material;
	}

	kite_driver::KiteDriverFrameBufferPtr KiteDriverShareObjectManager::GetTemporaryFrameBuffer()
	{
		return _temp_framebuffer_getter.GetTemporaryObject();
	}

	void KiteDriverShareObjectManager::ReleaseTemporaryFrameBuffer(const KiteDriverFrameBufferPtr& frame_buffer)
	{
		_temp_framebuffer_getter.ReleaseTemporaryObject(frame_buffer);
	}

	kite_driver::KiteDriverRenderTexturePtr KiteDriverShareObjectManager::GetTemporaryRenderTexture()
	{
		return _temp_rendertexture_getter.GetTemporaryObject();
	}

	void KiteDriverShareObjectManager::ReleaseTemporaryRenderTexture(const KiteDriverRenderTexturePtr& render_texture)
	{
		_temp_rendertexture_getter.ReleaseTemporaryObject(render_texture);
	}

	void KiteDriverShareObjectManager::InitializeFullScreenPlane()
	{
		_fullscreen_plane_drawer = std::make_shared<KiteDriverMeshDrawer>();
		_fullscreen_plane_drawer->SetMesh(KiteDriverGeometryGenerator::Plane(2.0f, 2.0f));
		_fullscreen_plane_drawer->BindData();
	}

	void KiteDriverShareObjectManager::InitializeTextureMaterial()
	{
		_texture_material = KiteDriverFastAccess::GenerateMaterialByShader(
			"/shader/texture.vertex",
			"/shader/texture.fragment"
		);
		_texture_material->Link();
	}

	void KiteDriverShareObjectManager::InitializeShareFrameBuffer()
	{

	}

}