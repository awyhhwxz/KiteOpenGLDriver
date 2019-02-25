#include "stdafx.h"
#include "RenderItem01.h"
#include "KiteDriverMouseController.h"
#include "KiteDriverGeometryGenerator.h"
#include "KiteDriverGrayPostEffect.h"
#include "KiteDriverBlurPostEffect.h"
#include "KiteDriverHighLightingPostEffect.h"
#include "KiteDriverFastAccess.h"

using namespace kite_math;
using namespace kite_util;

namespace kite_driver
{

	RenderItem01::RenderItem01()
	{
		_window_size_changed_event = std::make_shared<KiteDriverEvent<float, float>::EventArgsDelegate>(
			std::bind(&RenderItem01::OnWindowSizeChanged, this, std::placeholders::_1, std::placeholders::_2)
			);
		KiteDriverWindowManager::Instance()->WindowSizeChangedEvent.RegistryEvent(_window_size_changed_event);
	}


	RenderItem01::~RenderItem01()
	{
		KiteDriverWindowManager::Instance()->WindowSizeChangedEvent.UnregistryEvent(_window_size_changed_event);
	}

	void RenderItem01::Initialize()
	{
		InitializeShaderDemo();
	}
	void RenderItem01::Render()
	{
		ShaderDemo();
	}

	void RenderItem01::OnWindowSizeChanged(float width, float height)
	{
		if (_camera)
		{
			_camera->set_view_port(ViewPort(0, 0, width, height));
			_camera->set_aspect(width / height);
		}
	}

	void RenderItem01::ShaderDemo()
	{
		KiteDriverHighLightingManager::Instance()->RenderHighLighting(_scene->get_camera());
		//_rendertexture_scene->Render();
		_scene->Render();
	}
	void RenderItem01::InitializeShaderDemo()
	{
		_rendertexture = std::make_shared<KiteDriverRenderTexture>();

		_cubeRenderObject = GenerateCubeRenderObject();
		_planeRenderObject = GeneratePlaneRenderObject();

		_camera = GenerateCamera();
		KiteDriverWindowManager::Instance()->Refresh();

		auto mouse_controller = std::make_shared<kite_driver::KiteDriverMouseController>();
		mouse_controller->SetCamera(_camera);
		KiteDriverInputManager::Instance()->RegistryMouseMessageReceiver(std::static_pointer_cast<kite_driver::IMouseMessageReceiver>(mouse_controller));
		
		auto skybox = GenerateSkyBox();

		_scene = std::make_shared<KiteDriverScene>();
		_scene->AddRenderObj(_cubeRenderObject);
		_scene->AddRenderObj(_planeRenderObject);
		_scene->set_camera(_camera);
		_scene->SetSkyBox(skybox);
		_scene->SetPostEffect(std::make_shared<KiteDriverHighLightingPostEffect>());
		KiteDriverWindowManager::Instance()->set_window_scene(_scene);

		//KiteDriverHighLightingManager::Instance()->AddHighLightingObj(_planeRenderObject);
		//_rendertexture_scene = std::make_shared<KiteDriverScene>();
		//_rendertexture_scene->AddRenderObj(_cubeRenderObject);
		//_rendertexture_scene->set_camera(_camera);
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
		auto material = KiteDriverFastAccess::GenerateMaterialByShader(
			"/shader/texture.vertex",
			"/shader/texture.fragment"
		);

		return material;
	}

	kite_driver::KiteDriverCameraPtr RenderItem01::GenerateCamera()
	{
		KiteDriverCameraPtr camera = std::make_shared<KiteDriverCamera>();
		camera->set_near_plane(1.0f);
		camera->set_position(Vector3f(0, 0, -10.0f));
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

	kite_driver::KiteDriverRenderObjectPtr RenderItem01::GenerateCubeRenderObject()
	{
		KiteDriverRenderObjectPtr renderObj = std::make_shared<KiteDriverRenderObject>();

		auto mesh = KiteDriverFastAccess::LoadFbxMesh("/model/balloonstupidcat.fbx");
		renderObj->set_mesh(mesh);//KiteDriverGeometryGenerator::Cuboid(1.0f, 1.0f, 1.0f));

		auto material = KiteDriverFastAccess::GenerateMaterialByShader(
			"/shader/standard.vertex",
			"/shader/standard.fragment"
		);
		auto texture = KiteDriverFastAccess::GenerateTexture2D("/texture/balloonstupidcat_a.png");
		material->SetUniformTexture("_Albedo", texture);
		float smoothness = 0.5f;
		material->SetUniformValue("_Smoothness", KiteDriverParaValueType::KDPVT_FLOAT, &smoothness);
		float metallic = 0.5f;
		material->SetUniformValue("_Metallic", KiteDriverParaValueType::KDPVT_FLOAT, &metallic);

		renderObj->set_material(material);
		renderObj->Initialize();
		renderObj->set_position(Vector3f(0, 0, 0));
		renderObj->set_euler(Euler(-Mathf::PI * 0.5f, Mathf::PI, 0));
		renderObj->set_scale(Vector3f(0.01, 0.01, 0.01));

		return renderObj;
	}

	KiteDriverRenderObjectPtr RenderItem01::GeneratePlaneRenderObject()
	{
		KiteDriverRenderObjectPtr renderObj = std::make_shared<KiteDriverRenderObject>();
		renderObj->set_mesh(KiteDriverGeometryGenerator::Plane(1.0f, 1.0f));
		
		auto material = GenerateMaterial();
		auto texture = KiteDriverFastAccess::GenerateTexture2D("/texture/landscape.jpg");
		material->SetUniformTexture("tex", texture);

		renderObj->set_material(material);
		renderObj->Initialize();
		renderObj->set_position(Vector3f(0, 0, 0));
		renderObj->set_euler(Euler(0, 0, 0));
		renderObj->set_scale(Vector3f(1, 1, 1));
		return renderObj;
	}

}