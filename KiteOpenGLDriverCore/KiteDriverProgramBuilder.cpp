#include "stdafx.h"
#include "KiteDriverProgramBuilder.h"

namespace kite_driver
{

	KiteDriverProgramBuilder::KiteDriverProgramBuilder()
	{
	}


	KiteDriverProgramBuilder::~KiteDriverProgramBuilder()
	{
	}

	void KiteDriverProgramBuilder::Create()
	{
		_program = glCreateProgram();
	}

	void KiteDriverProgramBuilder::Destroy()
	{
		glDeleteProgram(_program);
	}

	void KiteDriverProgramBuilder::AttachShader(GLuint shader)
	{
		glAttachShader(_program, shader);
	}

	void KiteDriverProgramBuilder::LinkProgram()
	{
		glLinkProgram(_program);
		GLint linked = 0;
		glGetProgramiv(_program, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			GLint infoLen = 0;
			glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &infoLen);
		}
	}

	void KiteDriverProgramBuilder::Begin()
	{
		glUseProgram(_program);
		std::for_each(_uniformValueMap.begin(), _uniformValueMap.end(), [this](const std::pair<tstring, std::shared_ptr<KiteDriverParaValue>>& pair)
		{
			UniformValueSet(pair.first, pair.second.get());
		}); 
	}

	void KiteDriverProgramBuilder::End()
	{
		glUseProgram(0);
	}

	void KiteDriverProgramBuilder::SetUniformValue(tstring uniformName, KiteDriverParaValueType valueType, void* value)
	{
		auto targetUniformValue = _uniformValueMap.find(uniformName);

		std::shared_ptr<KiteDriverParaValue> paraValue;
		if (targetUniformValue == _uniformValueMap.end())
		{
			paraValue = std::make_shared<KiteDriverParaValue>();
			paraValue->SetType(valueType);
			_uniformValueMap.insert(std::pair<tstring, std::shared_ptr<KiteDriverParaValue>>(uniformName, paraValue));
		}
		else
		{
			paraValue = targetUniformValue->second;
		}

		paraValue->SetValue(value);
	}

	void KiteDriverProgramBuilder::UniformValueSet(tstring uniformName, KiteDriverParaValue * paraValue)
	{
		auto type = paraValue->get_type();
		auto value = paraValue->GetValue();
		switch (type)
		{
		case kite_driver::KDPVT_INVALID:
			break;
		case kite_driver::KDPVT_MATRIX4F:
			{
				auto location = glGetUniformLocation(_program, uniformName.c_str());
				if (location >= 0) glUniformMatrix4fv(location, 1, GL_FALSE, static_cast<const GLfloat*>(value));
			}
			break;
		default:
			break;
		}
	}

}
