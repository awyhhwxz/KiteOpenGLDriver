#include "stdafx.h"
#include "KiteDriverFastAccess.h"
#include "KiteDriverFbxVisitor.h"

namespace kite_driver
{
	
	kite_driver::KiteDriverMaterialPtr KiteDriverFastAccess::GenerateMaterialByShader(const tchar* vertex_shader_path, const tchar* fragment_shader_path)
	{
		auto material = std::make_shared<KiteDriverMaterial>();

		auto vertexPath = kite_util::PathUtil::GetResourcePath() + vertex_shader_path;
		auto fragmentPath = kite_util::PathUtil::GetResourcePath() + fragment_shader_path;
		material->SetShader(KDST_VERTEX_SHADER, vertexPath.c_str());
		material->SetShader(KDST_FRAGMENT_SHADER, fragmentPath.c_str());

		return material;
	}

	kite_driver::KiteDriverTexture2DPtr KiteDriverFastAccess::GenerateTexture2D(const tchar* image_path)
	{
		auto imagePath = kite_util::PathUtil::GetResourcePath() + image_path;
		kite_util::ImageLoader image_loader;
		image_loader.Load(imagePath.c_str());
		auto texture = std::make_shared<KiteDriverTexture2D>();
		texture->Assign(&image_loader);

		return texture;
	}

	KiteDriverMeshPtr KiteDriverFastAccess::LoadFbxMesh(const tchar * fbx_path)
	{
		auto fbx_full_path = kite_util::PathUtil::GetResourcePath() + fbx_path;
		KiteDriverFbxVisitor loader;
		loader.LoadFbx(fbx_full_path.c_str());
		return loader.FirstMesh();
	}

}