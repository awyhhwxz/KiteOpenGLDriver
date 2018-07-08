#pragma once

namespace kite_driver
{
	class KiteDriverProgramBuilder
	{
	public:
		KiteDriverProgramBuilder();
		~KiteDriverProgramBuilder();

		void Create();
		void Destroy();
		void AttachShader(GLuint shader);
		void LinkProgram();

		void Begin();
		void End();

		void SetUniformValue(tstring uniformName, KiteDriverParaValueType valueType, void* value);
		
	private:
		void UniformValueSet(tstring uniformName, KiteDriverParaValue * paraValue);

	protected:
		GLuint _program;
		std::map<tstring, std::shared_ptr<KiteDriverParaValue>> _uniformValueMap;
	};

}