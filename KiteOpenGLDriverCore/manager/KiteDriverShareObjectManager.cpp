#include "stdafx.h"
#include "KiteDriverShareObjectManager.h"
#include "KiteDriverGeometryGenerator.h"

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

	void KiteDriverShareObjectManager::InitializeFullScreenPlane()
	{
		_fullscreen_plane_drawer = std::make_shared<KiteDriverMeshDrawer>();
		_fullscreen_plane_drawer->SetMesh(KiteDriverGeometryGenerator::Plane(2.0f, 2.0f));
		_fullscreen_plane_drawer->BindData();
	}

	void KiteDriverShareObjectManager::InitializeTextureMaterial()
	{
		_texture_material = std::make_shared<KiteDriverMaterial>();
		auto vertexPath = kite_util::PathUtil::GetResourcePath() + "/shader/texture.vertex";
		auto fragmentPath = kite_util::PathUtil::GetResourcePath() + "/shader/texture.fragment";
		_texture_material->SetShader(KDST_VERTEX_SHADER, vertexPath.c_str());
		_texture_material->SetShader(KDST_FRAGMENT_SHADER, fragmentPath.c_str());

		_texture_material->Link();
	}

}