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

	void KiteDriverMaterial::SetShader(KiteDriverShaderType shaderType, std::string shaderPath)
	{
		_shaderMap[shaderType] = shaderPath;
	}

	void KiteDriverMaterial::Link()
	{
		std::for_each(_shaderMap.begin(), _shaderMap.end(), [this](auto shaderPair)
		{
			auto shaderType = KiteDriverEnumOpenGLEnumConverter::Convert(shaderPair.first);
			auto vertexShader = KiteDriverShaderVisitor::LoadShaderFile(shaderType, shaderPair.second.c_str());
			_programBuilder.AttachShader(vertexShader);
		});

		_programBuilder.LinkProgram();
	}

	void KiteDriverMaterial::BeginRender()
	{
		_programBuilder.Begin();
	}

	void KiteDriverMaterial::EndRender()
	{
		_programBuilder.End();
	}


}