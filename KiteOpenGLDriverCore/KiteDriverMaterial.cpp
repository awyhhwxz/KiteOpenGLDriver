#include "stdafx.h"
#include "KiteDriverMaterial.h"


namespace kite_driver
{
	KiteDriverMaterial::KiteDriverMaterial()
	{
		_programBuilder.Create();
	}


	KiteDriverMaterial::~KiteDriverMaterial()
	{
		_programBuilder.Destroy();
	}

	void KiteDriverMaterial::SetShader(KiteDriverShaderType shader_type, const tchar*  shader_path)
	{
		_shader_map[shader_type] = shader_path;
	}

	void KiteDriverMaterial::Link()
	{
		std::for_each(_shader_map.begin(), _shader_map.end(), [this](auto shaderPair)
		{
			auto shaderType = KiteDriverEnumOpenGLEnumConverter::Convert(shaderPair.first);
			auto vertexShader = KiteDriverShaderVisitor::LoadShaderFile(shaderType, shaderPair.second.c_str());
			_programBuilder.AttachShader(vertexShader);
		});

		_programBuilder.LinkProgram();
	}

	void KiteDriverMaterial::BeginRender()
	{
		_render_state_setter.StateSet();
		_programBuilder.Begin();
	}

	void KiteDriverMaterial::EndRender()
	{
		_programBuilder.End();
	}


	void KiteDriverMaterial::SetUniformValue(const tchar* uniform_name, KiteDriverParaValueType value_type, void* value)
	{
		_programBuilder.SetUniformValue(uniform_name, value_type, value);
	}

	void KiteDriverMaterial::SetUniformTexture(const tchar* uniform_name, const std::shared_ptr<KiteDriverTexture>& texture)
	{
		_programBuilder.SetUniformTexture(uniform_name, texture);
	}

}