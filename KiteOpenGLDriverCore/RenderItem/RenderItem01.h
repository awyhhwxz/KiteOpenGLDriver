#pragma once

namespace kite_driver
{

	class RenderItem01 : public IKiteDriverRenderItem
	{
	public:
		RenderItem01();
		~RenderItem01();

		virtual void Initialize() override;
		virtual void Render() override;

	private:
		void DrawTriangle();
		void ShaderDemo();
		void InitializeShaderDemo();

		std::shared_ptr<KiteDriverMaterial> _material;
		GLuint _vbo[2];
	};

}