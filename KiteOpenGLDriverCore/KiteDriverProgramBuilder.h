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

		void SetUniformValue(const tchar* uniformName, KiteDriverParaValueType valueType, void* value);
		void SetUniformTexture(const tchar* uniformName, const std::shared_ptr<KiteDriverTexture2D>& texture);
	private:
		void UniformValueSet(const tchar* uniformName, KiteDriverParaValue * para_value);
		void UniformTextureSet(const tchar* uniformName, KiteDriverTexture2D* texture, int texture_index);
	protected:
		GLuint _program;
		std::map<tstring, std::shared_ptr<KiteDriverParaValue>> _uniform_value_map;
		std::map<tstring, std::shared_ptr<KiteDriverTexture2D>> _uniform_texture_map;
	};

}