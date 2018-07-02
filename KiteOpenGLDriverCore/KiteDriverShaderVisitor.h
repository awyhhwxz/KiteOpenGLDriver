#pragma once

namespace kite_driver
{
	class KiteDriverShaderVisitor
	{
	public:
		static GLuint LoadShaderFile(GLenum type, const char * shaderPath);
		static GLuint LoadShader(GLenum type, const char * shaderSrc);
	};

}