#pragma once


namespace kite_driver
{
	class KiteDriverMaterial
	{
	public:
		KiteDriverMaterial();
		~KiteDriverMaterial();

	public:
		void SetShader(KiteDriverShaderType shader_type, const tchar* shader_path);
		void Link();
		void BeginRender();
		void EndRender();

		void SetUniformValue(const tchar* uniform_name, KiteDriverParaValueType value_type, void* value);
		void SetUniformTexture(const tchar* uniform_name, const std::shared_ptr<KiteDriverTexture>& texture);

		KiteDriverRenderStateSetter* get_render_state_setter() { return &_render_state_setter; }
	private:
		KiteDriverProgramBuilder _programBuilder;
		std::map<KiteDriverShaderType, std::string> _shader_map;
		KiteDriverRenderStateSetter _render_state_setter;
	};
	
	typedef std::shared_ptr<KiteDriverMaterial> KiteDriverMaterialPtr;
}