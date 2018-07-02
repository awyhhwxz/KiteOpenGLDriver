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


	void RenderItem01::DrawTriangle()
	{
		Vector3f v[3];
		v[0] = Vector3f(-1.0f, -1.0f, 0.0f);
		v[1] = Vector3f(1.0f, -1.0f, 0.0f);
		v[2] = Vector3f(0.0f, 1.0f, 0.0f);

		float values[3 * 3];
		for (int i = 0; i < 3; ++i)
		{
			memcpy(&values[i * 3], &v[i], sizeof(float) * 3);
		}

		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
	}

	void RenderItem01::ShaderDemo()
	{
		auto vertexPath = PathUtil::GetAppPath() + "/shader/vertex_shader.txt";
		auto fragmentPath = PathUtil::GetAppPath() + "/shader/fragment_shader.txt";

		KiteDriverProgramBuilder programBuilder;
		programBuilder.Create();
		auto vertexShader = KiteDriverShaderVisitor::LoadShaderFile(GL_VERTEX_SHADER, vertexPath.c_str());
		auto fragmentShader = KiteDriverShaderVisitor::LoadShaderFile(GL_FRAGMENT_SHADER, fragmentPath.c_str());
		programBuilder.AttachShader(vertexShader);
		programBuilder.AttachShader(fragmentShader);
		programBuilder.LinkProgram();

		programBuilder.Begin();
		{
			glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[1]);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
			glDisableVertexAttribArray(0);
		}
		programBuilder.End();
	}
	void RenderItem01::InitializeShaderDemo()
	{
		Vector3f v[3];
		v[0] = Vector3f(-1.0f, -1.0f, 0.0f);
		v[1] = Vector3f(1.0f, -1.0f, 0.0f);
		v[2] = Vector3f(0.0f, 1.0f, 0.0f);

		float values[3 * 3];
		for (int i = 0; i < 3; ++i)
		{
			memcpy(&values[i * 3], &v[i], sizeof(float) * 3);
		}

		GLushort indexes[] = { 2, 1, 0 };

		glGenBuffers(2, _vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

	}
}