#pragma once

namespace kite_driver
{
	class KiteDriverProgramBuilder
	{
	public:
		KiteDriverProgramBuilder();
		~KiteDriverProgramBuilder();

		void Create();
		void AttachShader(GLuint shader);
		void LinkProgram();

		void Begin();
		void End();
	protected:
		GLuint _program;
	};

}