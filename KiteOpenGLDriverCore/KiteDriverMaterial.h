#pragma once


namespace kite_driver
{
	class KiteDriverMaterial
	{
	public:
		KiteDriverMaterial();
		~KiteDriverMaterial();

	public:
		void SetShader(KiteDriverShaderType shaderType, std::string shaderPath);
		void Link();
		void BeginRender();
		void EndRender();

		void SetUniformValue(const tchar* uniformName, KiteDriverParaValueType valueType, void* value);
		void SetUniformTexture(const tchar* uniformName, const std::shared_ptr<KiteDriverTexture2D>& texture);
	private:
		KiteDriverProgramBuilder _programBuilder;
		std::map<KiteDriverShaderType, std::string> _shaderMap;
	};

}