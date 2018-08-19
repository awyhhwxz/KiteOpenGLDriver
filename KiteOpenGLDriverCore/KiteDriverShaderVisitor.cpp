#include "stdafx.h"
#include "KiteDriverShaderVisitor.h"
#include "KiteDriverShaderFileParser.h"

namespace kite_driver
{

	GLuint KiteDriverShaderVisitor::LoadShaderFile(GLenum type, const char * shaderPath)
	{
		auto shaderSrc = KiteDriverShaderFileParser::ReadShaderString(shaderPath);
		return LoadShader(type, shaderSrc.c_str());
	}

	GLuint KiteDriverShaderVisitor::LoadShader(GLenum type, const char * shaderSrc)
	{
		GLuint shader = glCreateShader(type);
		GLint compiled;

		if (shader == 0)
		{
			return 0;
		}

		glShaderSource(shader, 1, &shaderSrc, NULL);

		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (!compiled)
		{
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen > 1)
			{
				char* infoLog = (char*)malloc(sizeof(char) * infoLen);
				glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
				free(infoLog);
			}
			glDeleteShader(shader);
			return 0;
		}
		return shader;
	}

}