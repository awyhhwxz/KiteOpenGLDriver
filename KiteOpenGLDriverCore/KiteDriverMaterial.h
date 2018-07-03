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
	private:
		KiteDriverProgramBuilder _programBuilder;
		std::map<KiteDriverShaderType, std::string> _shaderMap;
	};

}