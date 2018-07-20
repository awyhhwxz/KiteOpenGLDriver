#include "stdafx.h"
#include "RenderItem01.h"
#include "KiteDriverMouseController.h"
#include "KiteDriverGeometryGenerator.h"

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
		glClearColor(1.0f, 0.0f, 0.0f, 1.f);
		glClearDepth(1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		ShaderDemo();
	}

	void RenderItem01::ShaderDemo()
	{
		_scene->Render();
	}
	void RenderItem01::InitializeShaderDemo()
	{
		_renderObject = std::make_shared<KiteDriverRenderObject>();
		_renderObject->set_mesh(KiteDriverGeometryGenerator::Cuboid(1.0f,1.0f,1.0f));
		_renderObject->set_material(GenerateMaterial());
		_renderObject->Initialize();
		_renderObject->set_position(Vector3f(0, 0, 0));
		_renderObject->set_euler(Euler(0, 0, Mathf::PI * 0.5f));
		_renderObject->set_scale(Vector3f(2, 2, 2));

		std::shared_ptr<KiteDriverCamera> camera = std::make_shared<KiteDriverCamera>();
		camera->set_position(Vector3f(2.0f, 0, -20.0f));

		KiteDriverWindowManager::Instance()->set_window_camera(camera);

		auto mouse_controller = std::make_shared<kite_driver::KiteDriverMouseController>();
		mouse_controller->SetCamera(camera);
		KiteDriverInputManager::Instance()->RegistryMouseMessageReceiver(std::static_pointer_cast<kite_driver::IMouseMessageReceiver>(mouse_controller));

		_scene = std::make_shared<KiteDriverScene>();
		_scene->AddRenderObj(_renderObject);
		_scene->set_camera(camera);

	}

	std::shared_ptr<KiteDriverMesh> RenderItem01::GenerateMesh()
	{
		std::shared_ptr<KiteDriverMesh> mesh = std::make_shared<KiteDriverMesh>();

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

		auto imagePath = PathUtil::GetResourcePath() + "/texture/stone.jpg";
		ImageLoader image_loader;
		image_loader.Load(imagePath.c_str());
		auto texture = std::make_shared<KiteDriverTexture2D>();
		texture->Assign(&image_loader);
		material->SetUniformTexture("tex", texture);

		auto vertexPath = PathUtil::GetResourcePath() + "/shader/texure.vertex";
		auto fragmentPath = PathUtil::GetResourcePath() + "/shader/texture.fragment";
		material->SetShader(KDST_VERTEX_SHADER, vertexPath);
		material->SetShader(KDST_FRAGMENT_SHADER, fragmentPath);

		return material;
	}

}