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
		void OnWindowSizeChanged(float width, float height);
		void ShaderDemo();
		void InitializeShaderDemo();

		KiteDriverMeshPtr GenerateMesh();
		std::shared_ptr<KiteDriverMaterial> GenerateMaterial();
		KiteDriverCameraPtr GenerateCamera();
		KiteDriverTextureCubePtr GenerateSkyBox();

		KiteDriverRenderObjectPtr GenerateCubeRenderObject();
		KiteDriverRenderObjectPtr GeneratePlaneRenderObject();

		KiteDriverRenderObjectPtr _cubeRenderObject;
		KiteDriverRenderObjectPtr _planeRenderObject;
		KiteDriverCameraPtr _camera;
		std::shared_ptr<KiteDriverScene> _scene;
		std::shared_ptr<KiteDriverScene> _rendertexture_scene;

		KiteDriverRenderTexturePtr _rendertexture;

		KiteDriverEvent<float, float>::EventArgsDelegatePtr _window_size_changed_event;
	};

}