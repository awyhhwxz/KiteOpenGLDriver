#include "stdafx.h"
#include "RenderItem01.h"
#include "KiteDriverMouseController.h"
#include "KiteDriverGeometryGenerator.h"
#include "KiteDriverGrayPostEffect.h"

using namespace kite_math;
using namespace kite_util;

namespace kite_driver
{

	RenderItem01::RenderItem01()
	{
	}


	RenderItem01::~RenderItem01()
	{
	}
	void RenderItem01::Initialize()
	{
		InitializeShaderDemo();
	}
	void RenderItem01::Render()
	{
		ShaderDemo();
	}

	void RenderItem01::ShaderDemo()
	{
		//_rendertexture_scene->Render();
		_scene->Render();
	}
	void RenderItem01::InitializeShaderDemo()
	{
		//_rendertexture = std::make_shared<KiteDriverRenderTexture>();

		_cubeRenderObject = GenerateCubeRenderObject();
		//_planeRenderObject = GeneratePlaneRenderObject();

		KiteDriverCameraPtr camera = GenerateCamera();

		auto mouse_controller = std::make_shared<kite_driver::KiteDriverMouseController>();
		mouse_controller->SetCamera(camera);
		KiteDriverInputManager::Instance()->RegistryMouseMessageReceiver(std::static_pointer_cast<kite_driver::IMouseMessageReceiver>(mouse_controller));
		
		auto skybox = GenerateSkyBox();

		_scene = std::make_shared<KiteDriverScene>();
		_scene->AddRenderObj(_cubeRenderObject);
		//_scene->AddRenderObj(_planeRenderObject);
		_scene->set_camera(camera);
		_scene->SetSkyBox(skybox);
		_scene->SetPostEffect(std::make_shared<KiteDriverGrayPostEffect>());

		//_rendertexture_scene = std::make_shared<KiteDriverScene>();
		//_rendertexture_scene->AddRenderObj(_cubeRenderObject);
		//_rendertexture_scene->set_camera(camera);
		//_rendertexture_scene->SetRenderTarget(_rendertexture);
		//_rendertexture_scene->SetSkyBox(skybox);
	}

	KiteDriverMeshPtr RenderItem01::GenerateMesh()
	{
		KiteDriverMeshPtr mesh = std::make_shared<KiteDriverMesh>();

		Vector3f v[] = {
			Vector3f(-1.0f, -1.0f, 0.0f),
			Vector3f(1.0f, -1.0f, 0.0f),
			Vector3f(0.0f, 1.0f, 0.0f),
		};
		mesh->SetVertices(v, 3);

		GLushort indexes[] = { 2, 1, 0 };
		mesh->SetIndices(indexes, 3);
		return mesh;
	}

	std::shared_ptr<kite_driver::KiteDriverMaterial> RenderItem01::GenerateMaterial()
	{
		auto material = std::make_shared<KiteDriverMaterial>();

		auto vertexPath = PathUtil::GetResourcePath() + "/shader/texture.vertex";
		auto fragmentPath = PathUtil::GetResourcePath() + "/shader/texture.fragment";
		material->SetShader(KDST_VERTEX_SHADER, vertexPath.c_str());
		material->SetShader(KDST_FRAGMENT_SHADER, fragmentPath.c_str());

		return material;
	}

	kite_driver::KiteDriverCameraPtr RenderItem01::GenerateCamera()
	{
		KiteDriverCameraPtr camera = std::make_shared<KiteDriverCamera>();
		camera->set_position(Vector3f(2.0f, 0, -20.0f));

		KiteDriverWindowManager::Instance()->set_window_camera(camera);
		return camera;
	}

	kite_driver::KiteDriverTextureCubePtr RenderItem01::GenerateSkyBox()
	{
		KiteDriverTextureCubePtr texCube = std::make_shared<KiteDriverTextureCube>();
		ImageLoader loads[6];
		loads[0].Load(CSTR(PathUtil::GetResourcePath() + "/texture/skybox/leftImage.png"));
		loads[1].Load(CSTR(PathUtil::GetResourcePath() + "/texture/skybox/rightImage.png"));
		loads[2].Load(CSTR(PathUtil::GetResourcePath() + "/texture/skybox/upImage.png"));
		loads[3].Load(CSTR(PathUtil::GetResourcePath() + "/texture/skybox/downImage.png"));
		loads[4].Load(CSTR(PathUtil::GetResourcePath() + "/texture/skybox/backImage.png"));
		loads[5].Load(CSTR(PathUtil::GetResourcePath() + "/texture/skybox/frontImage.png"));
		texCube->Assign(loads);

		return texCube;
	}

	KiteDriverTexture2DPtr RenderItem01::GenerateTexture2D(const tchar* image_path)
	{
		auto imagePath = PathUtil::GetResourcePath() + image_path;
		ImageLoader image_loader;
		image_loader.Load(imagePath.c_str());
		auto texture = std::make_shared<KiteDriverTexture2D>();
		texture->Assign(&image_loader);

		return texture;
	}

	kite_driver::KiteDriverRenderObjectPtr RenderItem01::GenerateCubeRenderObject()
	{
		KiteDriverRenderObjectPtr renderObj = std::make_shared<KiteDriverRenderObject>();
		renderObj->set_mesh(KiteDriverGeometryGenerator::Cuboid(1.0f, 1.0f, 1.0f));

		auto material = GenerateMaterial();
		auto texture = GenerateTexture2D("/texture/stone.jpg");
		material->SetUniformTexture("tex", texture);

		renderObj->set_material(material);
		renderObj->Initialize();
		renderObj->set_position(Vector3f(0, 0, 0));
		renderObj->set_euler(Euler(0, 0, Mathf::PI * 0.5f));
		renderObj->set_scale(Vector3f(2, 2, 2));

		return renderObj;
	}

	KiteDriverRenderObjectPtr RenderItem01::GeneratePlaneRenderObject()
	{
		KiteDriverRenderObjectPtr renderObj = std::make_shared<KiteDriverRenderObject>();
		renderObj->set_mesh(KiteDriverGeometryGenerator::Plane(1.0f, 1.0f));
		
		auto material = GenerateMaterial();
		auto texture = GenerateTexture2D("/texture/landscape.jpg");
		material->SetUniformTexture("tex", _rendertexture);

		renderObj->set_material(material);
		renderObj->Initialize();
		renderObj->set_position(Vector3f(5, 0, 0));
		renderObj->set_euler(Euler(0, 0, 0));
		renderObj->set_scale(Vector3f(1, 1, 1));
		return renderObj;
	}

}