#include "stdafx.h"
#include "KiteDriverSkyBox.h"
#include "KiteDriverGeometryGenerator.h"


namespace kite_driver
{
	KiteDriverSkyBox::KiteDriverSkyBox()
	{
		_mesh = KiteDriverGeometryGenerator::SkyBoxMesh();
		
		_material = std::make_shared<KiteDriverMaterial>();

		auto vertexPath = kite_util::PathUtil::GetResourcePath() + "/shader/skybox.vertex";
		auto fragmentPath = kite_util::PathUtil::GetResourcePath() + "/shader/skybox.fragment";
		_material->SetShader(KDST_VERTEX_SHADER, vertexPath.c_str());
		_material->SetShader(KDST_FRAGMENT_SHADER, fragmentPath.c_str());
		_material->get_render_state_setter()->SetZWriteEnable(false);

		_object.set_mesh(_mesh);
		_object.set_material(_material);
		_object.Initialize();
	}


	KiteDriverSkyBox::~KiteDriverSkyBox()
	{
	}

	void KiteDriverSkyBox::SetTextureCube(const std::shared_ptr<KiteDriverTextureCube>& texCube)
	{
		_textureCube = texCube;
		_material->SetUniformTexture("texCube", _textureCube);
	}

	kite_driver::KiteDriverRenderObject* KiteDriverSkyBox::GetRenderObject()
	{
		if (!IsEmpty())
		{
			return &_object;
		}

		return nullptr;
	}

	bool KiteDriverSkyBox::IsEmpty()
	{
		return _textureCube.get() == nullptr;
	}

}