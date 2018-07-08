#include "stdafx.h"
#include "RenderItem01.h"

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

		//DrawTriangle();
		ShaderDemo();
	}

	void RenderItem01::ShaderDemo()
	{
		_renderObject->Render();
	}
	void RenderItem01::InitializeShaderDemo()
	{
		_renderObject = std::make_shared<KiteDriverRenderObject>();
		_renderObject->Mesh = GenerateMesh();
		_renderObject->Material = GenerateMaterial();
		_renderObject->Initialize();
		_renderObject->set_position(Vector3f(0.5f, 0, 0));
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

		auto vertexPath = PathUtil::GetAppPath() + "/shader/vertex_shader.txt";
		auto fragmentPath = PathUtil::GetAppPath() + "/shader/fragment_shader.txt";
		material->SetShader(KDST_VERTEX_SHADER, vertexPath);
		material->SetShader(KDST_FRAGMENT_SHADER, fragmentPath);

		return material;
	}

}