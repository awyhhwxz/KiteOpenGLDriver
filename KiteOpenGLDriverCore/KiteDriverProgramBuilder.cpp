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
	}

	void KiteDriverProgramBuilder::End()
	{
		glUseProgram(0);
	}

}
