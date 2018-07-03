#include "stdafx.h"
#include "KiteDriverEnumOpenGLEnumConverter.h"


namespace kite_driver
{
	GLenum KiteDriverEnumOpenGLEnumConverter::Convert(KiteDriverShaderType shaderType)
	{
		switch (shaderType)
		{
		case  KDST_VERTEX_SHADER:
			return GL_VERTEX_SHADER;
		case  KDST_FRAGMENT_SHADER:
			return GL_FRAGMENT_SHADER;
		default:
			return 0;
		}
	}
}