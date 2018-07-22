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
		std::for_each(_uniform_value_map.begin(), _uniform_value_map.end(), [this](const std::pair<tstring, std::shared_ptr<KiteDriverParaValue>>& pair)
		{
			UniformValueSet(pair.first.c_str(), pair.second.get());
		}); 

		auto uniform_texture_iterator = _uniform_texture_map.begin();
		int texture_i = 0;
		for (; uniform_texture_iterator != _uniform_texture_map.end(); ++texture_i, ++uniform_texture_iterator)
		{
			UniformTextureSet(uniform_texture_iterator->first.c_str(), uniform_texture_iterator->second.get(), texture_i);
		}
	}

	void KiteDriverProgramBuilder::End()
	{
		glUseProgram(0);
	}

	void KiteDriverProgramBuilder::SetUniformValue(const tchar* uniformName, KiteDriverParaValueType valueType, void* value)
	{
		auto targetUniformValue = _uniform_value_map.find(uniformName);

		std::shared_ptr<KiteDriverParaValue> paraValue;
		if (targetUniformValue == _uniform_value_map.end())
		{
			paraValue = std::make_shared<KiteDriverParaValue>();
			paraValue->SetType(valueType);
			_uniform_value_map.insert(std::pair<tstring, std::shared_ptr<KiteDriverParaValue>>(uniformName, paraValue));
		}
		else
		{
			paraValue = targetUniformValue->second;
		}

		paraValue->SetValue(value);
	}

	void KiteDriverProgramBuilder::SetUniformTexture(const tchar*  uniformName, const std::shared_ptr<KiteDriverTexture>& texture)
	{
		_uniform_texture_map[uniformName] = texture;

		auto targetUniformTexture = _uniform_texture_map.find(uniformName);
		if (targetUniformTexture == _uniform_texture_map.end())
		{
			_uniform_texture_map.insert(std::pair<tstring, std::shared_ptr<KiteDriverTexture>>(uniformName, texture));
		}
		else
		{
			targetUniformTexture->second = texture;
		}
	}

	void KiteDriverProgramBuilder::UniformTextureSet(const tchar* uniformName, KiteDriverTexture * texture, int texture_index)
	{
		auto location = glGetUniformLocation(_program, uniformName);
		if (location >= 0)
		{
			glActiveTexture(GL_TEXTURE0 + texture_index);
			texture->BindTexture();
			glUniform1i(location, texture_index);
		}
	}

	void KiteDriverProgramBuilder::UniformValueSet(const tchar* uniformName, KiteDriverParaValue * para_value)
	{
		auto type = para_value->get_type();
		auto value = para_value->GetValue();
		switch (type)
		{
		case kite_driver::KDPVT_INVALID:
			break;
		case kite_driver::KDPVT_MATRIX4F:
			{
				auto location = glGetUniformLocation(_program, uniformName);
				if (location >= 0) glUniformMatrix4fv(location, 1, GL_FALSE, static_cast<const GLfloat*>(value));
			}
			break;
		default:
			break;
		}
	}

}
