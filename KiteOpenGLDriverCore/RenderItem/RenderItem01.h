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
		void ShaderDemo();
		void InitializeShaderDemo();

		std::shared_ptr<KiteDriverMesh> GenerateMesh();
		std::shared_ptr<KiteDriverMaterial> GenerateMaterial();

		std::shared_ptr<KiteDriverRenderObject> _renderObject;
	};

}